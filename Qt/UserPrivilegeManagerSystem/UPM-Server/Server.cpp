#include "Server.h"
#include "SResultCode.h"
#include "SSqlConnectionPool.h"
#include "SHttpPartParse.h"
#include "SJwt.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <qfile.h>
#include<qfileinfo.h>
#include<qdir.h>

#include <optional>

#define CheckJsonParse(request) QJsonParseError error;auto jdom = QJsonDocument::fromJson(request.body(), &error);if (error.error != QJsonParseError::NoError)return SResult::failure(SResultCode::ParamJsonInvalid);
#define CheckQueryExec(query)if (query.lastError().type() != QSqlError::NoError)return SResult::failure(SResultCode::ServerSqlQueryError);
QJsonObject RecordToJsonObject(const QSqlRecord& record);

const char* secret = "HelloWorld";

std::optional<QByteArray>CheckToken(const QHttpServerRequest& request)
{
	//校验token
	auto auth = request.value("Authorization");
	//如果没有认证头
	if (auth.isEmpty())return SResult::failure(SResultCode::UserNotLogin);
	//必须以Bearer开头
	if (!auth.startsWith("Bearer"))return SResult::failure(SResultCode::UserNotLogin, "token格式错误");
	//获取token
	auto token = auth.mid(strlen("Bearer"));
	//验证token
	auto jwtObj = SJwt::SJwtObject::decode(token, SJwt::SAlgorithm::HS256, secret);
	if (jwtObj.status() == SJwt::SJwtObject::Status::Expired)return SResult::failure(SResultCode::UserNotLogin, "token已过期");
	if (!jwtObj.isValid())return SResult::failure(SResultCode::UserNotLogin, "token无效");
	//没有值就说明成功了
	return {};
}

Server::Server()
{
	//开启服务器
	m_server.listen(QHostAddress::Any, 8888);

	//添加路径丢失处理
	m_server.setMissingHandler([](const QHttpServerRequest& request, QHttpServerResponder&& responder) {
		QJsonObject jobj;
		jobj.insert("code", "001");
		jobj.insert("message", "不支持的api路径");
		responder.write(QJsonDocument(jobj));
		});

	//添加路由
	//获取服务器版本信息
	m_server.route("/api/version", [](const QHttpServerRequest& request) {
		QJsonObject jobj;
		jobj.insert("version", "1.0.1");
		jobj.insert("name", "userPrivilegeManager-server");
		jobj.insert("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
		return QJsonDocument(jobj).toJson(QJsonDocument::Compact);
		});

	//用户登录
	m_server.route("/api/login", [](const QHttpServerRequest& request) {
		CheckJsonParse(request)

			SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.prepare("SELECT * FROM users WHERE user_id=? AND password=? AND isDeleted=FALSE LIMIT 1");
		query.bindValue(0, jdom["user_id"]);
		query.bindValue(1, jdom["password"]);

		if (!query.exec())return SResult::failure(SResultCode::ServerSqlQueryError);
		if (!query.next())return SResult::failure(SResultCode::UserLoginError);
		if (!query.value("isEnable").toBool())return SResult::failure(SResultCode::UserAccountDisable);

		//验证成功时，生成token并返回（jwt）
		QJsonObject payload = {
			{"user_id", jdom["user_id"]},
			{"iat",QDateTime::currentDateTime().toString(Qt::DateFormat::ISODate)},
			{"exp",QDateTime::currentDateTime().addDays(7).toString(Qt::DateFormat::ISODate)}
		};
		SJwt::SJwtObject jwtObj(SJwt::SAlgorithm::HS256, payload, secret);
		qDebug() << jwtObj.jwt();
		return SResult::success({ {"token",QString(jwtObj.jwt())} });
		});

	//用户注册
	m_server.route("/api/register", [](const QHttpServerRequest& request) {
		CheckJsonParse(request)

			SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.prepare("INSERT IGNORE INTO users(user_id,username,password) VALUES(?,?,?)");
		query.bindValue(0, jdom["user_id"].toString());
		query.bindValue(1, jdom["username"].toString());
		query.bindValue(2, jdom["password"].toString());
		query.exec();
		CheckQueryExec(query);

		if (query.numRowsAffected() == 0)
		{
			return SResult::failure(SResultCode::UserAccountExists);
		}

		return SResult::success();

		});

	//用户列表(可按需查找)
	m_server.route("/api/user/list", [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		auto uquery = request.query();
		auto user_id = uquery.queryItemValue("user_id");
		auto isEnable = uquery.queryItemValue("isEnable");
		auto page = uquery.queryItemValue("page").toInt();
		auto pageSize = uquery.queryItemValue("pageSize").toInt();
		auto queryValue = uquery.queryItemValue("query");

		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());

		//获取总记录条数
		QString filter = "WHERE isDeleted=FALSE ";
		if (!user_id.isEmpty())
			filter += QString("AND user_id=%1 ").arg(user_id);
		else if (!queryValue.isEmpty())
			filter += QString("AND user_id LIKE '%%1%' OR username LIKE '%%1%' OR email LIKE '%%1%' OR telephone LIKE '%%1%' ").arg(queryValue);
		if (!isEnable.isEmpty())
			filter += QString("AND isEnable=%1 ").arg(isEnable == "true" ? 1 : 0);
		query.exec(QString("SELECT COUNT(*) total FROM users %1").arg(filter));
		CheckQueryExec(query);
		query.next();
		int total = query.value("total").toInt();

		if (pageSize <= 0)pageSize = 20;
		int last_page = total / pageSize + (total % pageSize == 0 ? 0 : 1);
		if (page > last_page || page < 1)page = 1;

		QString sql = "SELECT id,user_id,username,gender,telephone,email,isEnable FROM users ";
		sql += filter;
		sql += QString("LIMIT %1,%2").arg((page - 1) * pageSize).arg(pageSize);

		//qDebug() << "sql: " << sql;
		query.exec(sql);
		CheckQueryExec(query);

		QJsonObject jobj;
		if (query.size() > 0)
		{
			QJsonArray jarr;
			int cnt = query.record().count();

			while (query.next())
			{
				jarr.append(RecordToJsonObject(query.record()));
			}
			jobj.insert("lists", jarr);
			jobj.insert("cur_page", page);
			jobj.insert("page_size", pageSize);
			jobj.insert("last_page", last_page);
			jobj.insert("total", total);
		}

		return SResult::success(jobj);

		});

	//用户创建
	m_server.route("/api/user/create", [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		CheckJsonParse(request)

		//检查创建需要的user_id、username和password是否存在
		if (!(jdom.object().contains("user_id") && jdom.object().contains("username") && jdom.object().contains("password")))return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");

		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.prepare("INSERT IGNORE INTO users(user_id,username,password) VALUES(?,?,?)");
		query.bindValue(0, jdom["user_id"].toString());
		query.bindValue(1, jdom["username"].toString());
		query.bindValue(2, jdom["password"].toString());
		query.exec();
		CheckQueryExec(query);

		if (query.numRowsAffected() == 0)
		{
			return SResult::failure(SResultCode::UserAccountExists);
		}

		return SResult::success();

		});

	//用户批量创建
	m_server.route("/api/user/batch_create", [](const QHttpServerRequest& request){
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		CheckJsonParse(request)

		SConnectionWrap wrap;
		auto db = wrap.openConnection();
		db.transaction();
		QSqlQuery query(db);
		query.prepare("INSERT IGNORE INTO users(user_id,username,password) VALUES(?,?,?)");
		auto rootObj = jdom.object();
		auto jarr = rootObj.value("lists").toArray();
		for (size_t i = 0; i < jarr.size(); i++)
		{
			auto subObj = jarr[i].toObject();
			//检查创建需要的user_id、username是否存在
			if (!(subObj.contains("user_id") && subObj.contains("username")))
			{
				db.rollback();
				return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");
			}
			query.bindValue(0, subObj["user_id"].toString());
			query.bindValue(1, subObj["username"].toString());
			query.bindValue(2, subObj["password"].toString());
			query.exec();
			if (!query.exec())
			{
				db.rollback();
				return SResult::failure(SResultCode::ServerSqlQueryError);
			}

		}
		db.commit();


		if (query.numRowsAffected() == 0)
		{
			return SResult::failure(SResultCode::UserAccountExists);
		}

		return SResult::success();

		});


	//用户删除
	m_server.route("/api/user/delete", [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		CheckJsonParse(request)

			auto jarr = jdom["lists"].toArray();
		if (jarr.isEmpty())return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");

		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.prepare("UPDATE users SET isDeleted=TRUE WHERE user_id=?");

		for (int i = 0; i < jarr.size(); i++)
		{
			query.bindValue(0, jarr[i].toString());
			query.exec();
			CheckQueryExec(query);
		}

		return SResult::success();

		});

	//用户修改
	m_server.route("/api/user/alter", [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		//先把必要的user_id拿出来
		if (!request.query().hasQueryItem("user_id"))return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");
		auto user_id = request.query().queryItemValue("user_id");

		CheckJsonParse(request)

			auto robj = jdom.object();
		QString update_str = "";
		if (robj.contains("username"))update_str += QString("username='%1',").arg(robj.value("username").toString());
		if (robj.contains("password"))update_str += QString("password='%1',").arg(robj.value("password").toString());
		if (robj.contains("email"))update_str += QString("email='%1',").arg(robj.value("email").toString());
		if (robj.contains("telephone"))update_str += QString("telephone='%1',").arg(robj.value("telephone").toString());
		if (robj.contains("gender"))update_str += QString("gender='%1',").arg(robj.value("gender").toString());
		//截断最后一个逗号
		update_str.chop(1);

		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.exec(QString("UPDATE users SET %1 WHERE user_id='%2'").arg(update_str).arg(user_id));
		CheckQueryExec(query);

		if (query.numRowsAffected() == 0)
		{
			return SResult::failure(SResultCode::Success, "成功且无数据");
		}



		return SResult::success();

		});

	//用户批量修改
	m_server.route("/api/user/batch_alter", [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		CheckJsonParse(request)

			QString resultSql = "";
		auto jarr = jdom["lists"].toArray();
		if (jarr.isEmpty())return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");

		for (size_t i = 0; i < jarr.size(); i++)
		{
			auto jobj = jarr.at(i).toObject();
			auto fobj = jobj.value("filter").toObject();
			auto uobj = jobj.value("update").toObject();

			QString filter;
			for (auto it = fobj.begin(); it != fobj.end(); it++)
			{
				if (it.key() == "id")filter += QString("id='%1' AND ").arg(it.value().toString());
				else if (it.key() == "user_id")filter += QString("user_id='%1' AND ").arg(it.value().toString());
				else if (it.key() == "isEnable")filter += QString("isEnable=%1 AND ").arg(it.value().toInt());
				else if (it.key() == "isDeleted")filter += QString("isDeleted=%1 AND ").arg(it.value().toInt());
			}
			filter.chop(5);

			QString update_str = "";
			for (auto it = uobj.begin(); it != uobj.end(); it++)
			{

				if (it.key() == "username")update_str += QString("username='%1',").arg(it.value().toString());
				else if (it.key() == "password")update_str += QString("password='%1',").arg(it.value().toString());
				else if (it.key() == "email")update_str += QString("email='%1',").arg(it.value().toString());
				else if (it.key() == "telephone")update_str += QString("telephone='%1',").arg(it.value().toString());
				else if (it.key() == "gender")update_str += QString("gender=%1,").arg(it.value().toInt());
				else if (it.key() == "isEnable")update_str += QString("isEnable=%1,").arg(it.value().toInt());
			}
			//截断最后一个逗号
			update_str.chop(1);
			QString sql = QString("UPDATE users SET %1 WHERE %2;").arg(update_str).arg(filter);
			resultSql.append(sql);
		}
		qDebug() << "resultSql: " << resultSql;
		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.exec(resultSql);
		CheckQueryExec(query);

		if (query.numRowsAffected() == 0)
		{
			return SResult::failure(SResultCode::Success, "成功且无数据");
		}

		return SResult::success();
		});

	//用户头像上传（修改）只接收post请求
	m_server.route("/api/user/avatar", QHttpServerRequest::Method::Post, [](const QHttpServerRequest& request) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			return ret.value();
		}

		//先把必要的user_id拿出来
		if (!request.query().hasQueryItem("user_id"))return SResult::failure(SResultCode::ParamLoss, "缺少必要的参数");

		auto user_id = request.query().queryItemValue("user_id");
		auto data = request.body();
		SHttpPartParse p(data);
		if (!p.parse())
		{
			qDebug() << "parse error";
			return SResult::failure(SResultCode::ParamParseError);
		}

		//创建保存头像的路径
		auto avatar_path = "images/avatar/";
		QDir dir;
		if (!dir.exists(avatar_path))dir.mkpath(avatar_path);

		QFile file(avatar_path + user_id  + "." + QFileInfo(p.filename()).suffix());

		if (!file.open(QIODevice::WriteOnly))return SResult::failure(SResultCode::ServerInnerError, "头像文件保存失败");

		file.write(p.data());

		//把头像路径保存到数据库
		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.exec(QString("UPDATE users SET avatar_path='%1' WHERE user_id='%2' AND isDeleted=FALSE").arg(file.fileName()).arg(user_id));
		CheckQueryExec(query);

		//if (query.numRowsAffected() == 0)return SResult::failure(SResultCode::SuccessButNotData);



		qDebug() << "name: " << p.name();
		qDebug() << "filename: " << p.filename();

		file.close();
		return SResult::success();
		});

	//用户头像下载（获取）只接收get请求
	m_server.route("/api/user/avatar", QHttpServerRequest::Method::Get, [](const QHttpServerRequest& request, QHttpServerResponder&& responder) {
		std::optional<QByteArray> ret = CheckToken(request);
		if (ret.has_value())
		{
			responder.write(ret.value(), "application/json");
			return;
		}

		//先把必要的user_id拿出来
		if (!request.query().hasQueryItem("user_id"))
		{
			responder.write(SResultCode::ParamLoss.toJson(), "application/json");
			return;
		}
		auto user_id = request.query().queryItemValue("user_id");

		//从数据库获取头像路径
		SConnectionWrap wrap;
		QSqlQuery query(wrap.openConnection());
		query.prepare("SELECT avatar_path FROM users WHERE user_id=? AND isDeleted=FALSE");
		query.bindValue(0, user_id);
		if (!query.exec())
		{
			responder.write(SResultCode::ServerSqlQueryError.toJson(), "application/json");
			return;
		}
		if (!query.next())
		{
			responder.write(SResultCode::SuccessButNotData.toJson(), "application/json");
			return;
		}

		//读取头像文件
		auto avatar_path = query.value("avatar_path").toString();
		QFile file(avatar_path);
		if (!file.open(QIODevice::ReadOnly))
		{
			responder.write(SResult::failure(SResultCode::ServerResourceNotFound, "头像文件读取失败"), "application/json");
			return;
		}

		responder.writeStatusLine();
		responder.writeHeader("Content-Type", QString("image/%1").arg(QFileInfo(avatar_path).suffix()).toUtf8());
		responder.writeHeader("Content-Length", QByteArray::number(file.size()));
		responder.writeHeader("Content-Disposition", QString("attachment; filename=%1").arg(QFileInfo(avatar_path).fileName()).toUtf8());
		responder.writeBody(file.readAll());


		file.close();
		});

}
QJsonObject RecordToJsonObject(const QSqlRecord& record)
{
	QJsonObject juser;
	for (int i = 0; i < record.count(); i++)
	{
		const auto& v = record.value(i);
		switch (v.typeId())
		{
		case QMetaType::Bool:
			juser.insert(record.fieldName(i), v.toBool());
			break;
		case QMetaType::Int:
		case QMetaType::UInt:
		case QMetaType::LongLong:
		case QMetaType::ULongLong:
		case QMetaType::Long:
		case QMetaType::Short:
		case QMetaType::ULong:
		case QMetaType::UShort:
			juser.insert(record.fieldName(i), v.toLongLong());
			break;
		case QMetaType::Float:
		case QMetaType::Double:
			juser.insert(record.fieldName(i), v.toDouble());
			break;
		default:
			juser.insert(record.fieldName(i), v.toString());
			break;
		}
	}
	return juser;
}
