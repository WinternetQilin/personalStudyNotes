#ifndef SRESULTCODE_H_
#define SRESULTCODE_H_
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
class SResultCode
{
	struct  Code
	{
		int code;
		const char* codeStr;
		const char* message;

		Code(int code, const char* codeStr, const char* message)
			:code(code),codeStr(codeStr),message(message)
		{

		}

		QByteArray toJson()const
		{
			QJsonObject jobj;
			jobj.insert("code", code);
			jobj.insert("message", message);
			return QJsonDocument(jobj).toJson(QJsonDocument::Compact);
		}

		operator QJsonValue() const
		{
			return code;
		}
	};

public:
#define CODE(name,value,message) inline static Code name{value,#name,message}
	CODE(Success, 0, "操作成功");
	CODE(SuccessButNotData, 1, "操作成功，但没有返回数据");
	//参数错误相关(1000~1999)
	CODE(ParamJsonInvalid, 1000, "请求参数Json无效");
	CODE(ParamLoss, 1001, "请求参数缺失");
	CODE(ParamParseError, 1002, "请求参数解析错误");
	//服务器错误相关(2000~2999)
	CODE(ServerSqlQueryError, 2000, "Sql执行失败");
	CODE(ServerInnerError, 2001, "服务器内部错误");
	CODE(ServerResourceNotFound, 2002, "服务器资源未找到");
	//用户错误相关(3000~3999)
	CODE(UserAccountDisable, 3000, "账户已被禁用，请联系管理员");
	CODE(UserLoginError, 3001, "登录失败，账号或密码不正确");
	CODE(UserAccountExists, 3002, "账号已存在");
	CODE(UserNotLogin, 3003, "用户未登录");

#undef CODE
	friend class SResult;
};

#endif // !SRESULTCODE_H_

class SResult
{
public:
	static QByteArray success()
	{
		return SResultCode::Success.toJson();
	}
	static QByteArray success(const SResultCode::Code& code)
	{
		return code.toJson();
	}
	static QByteArray success(const QJsonObject& data)
	{
		QJsonObject jobj;
		jobj.insert("code", SResultCode::Success);
		jobj.insert("message", SResultCode::Success.message);
		jobj.insert("data", data);
		return QJsonDocument(jobj).toJson(QJsonDocument::Compact);
	}
	/*static QByteArray successButNotData()
	{
		QJsonObject jobj;
		jobj.insert("code", SResultCode::Success);
		jobj.insert("message", "操作成功，但没有返回数据");
		return QJsonDocument(jobj).toJson(QJsonDocument::Compact);
	}*/

	static QByteArray failure(const SResultCode::Code& code)
	{
		return code.toJson();
	}
	static QByteArray failure(const SResultCode::Code& code,const QString& message)
	{
		QJsonObject jobj;
		jobj.insert("code", code.code);
		jobj.insert("message", message);
		return QJsonDocument(jobj).toJson(QJsonDocument::Compact);
	}

};
