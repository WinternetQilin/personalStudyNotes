#include "UserDetailsDlg.h"
#include "UserDetailsDlg.h"
#include "UserDetailsDlg.h"
#include"SApp.h"
#include"SHttpClient.h"

#include<qboxlayout.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qformlayout.h>
#include<qfiledialog.h>
#include<qstandardpaths.h>
#include<qmessagebox.h>
#include<qhttpmultipart.h>

UserDetailsDlg::UserDetailsDlg(QWidget* parent)
	:QWidget(parent)
{
	init();
}

void UserDetailsDlg::init()
{
	setStyleSheet("background-color:white;");
	setAttribute(Qt::WA_StyledBackground);
	//窗口主布局
	auto mlayout = new QVBoxLayout(this);

	//返回按钮
	auto backBtn = new QPushButton("返回");
	//设置按钮大小策略：固定大小
	backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mlayout->addWidget(backBtn);
	//添加空白行
	mlayout->addSpacerItem(new QSpacerItem(30, 30));

	//基本信息展示布局
	auto hlayout = new QHBoxLayout();
	hlayout->addWidget(new QLabel("用户基本信息"));

	auto baseInfoEditBtn = new QPushButton("编辑基本信息");
	auto resetPwdBtn = new QPushButton("重置密码");
	auto deleteUserBtn = new QPushButton("删除用户");
	auto avatarAlterBtn = new QPushButton("更换头像");

	hlayout->addWidget(baseInfoEditBtn);
	hlayout->addWidget(resetPwdBtn);
	hlayout->addWidget(deleteUserBtn);
	hlayout->addStretch();

	mlayout->addLayout(hlayout);

	{
		m_user_id_lab = new QLabel();
		m_user_name_lab = new QLabel();
		m_user_email_lab = new QLabel();
		m_user_mobile_lab = new QLabel();
		m_avatar_lab = new QLabel();

		m_avatar_lab->setPixmap(QPixmap(":/Resource/default_avatar.jpg"));
		m_avatar_lab->setFixedSize(40, 40);
		m_avatar_lab->setScaledContents(true);
		//设置掩码，将其展示为圆形头像
		m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));

		auto alayout = new QHBoxLayout();
		alayout->addWidget(m_avatar_lab);
		alayout->addWidget(avatarAlterBtn);

		//左侧信息列表
		auto lflayout = new QFormLayout();
		lflayout->addRow("头 像：", alayout);
		lflayout->addRow("用户ID：", m_user_id_lab);
		lflayout->addRow("用户名：", m_user_name_lab);

		//右侧信息列表
		auto rflayout = new QFormLayout();
		rflayout->addRow("手机号码：", m_user_mobile_lab);
		rflayout->addRow("电子邮箱：", m_user_email_lab);

		auto hlayout = new QHBoxLayout();
		hlayout->addLayout(lflayout);
		hlayout->addLayout(rflayout);
		mlayout->addLayout(hlayout);
	}
	mlayout->addStretch();

	connect(avatarAlterBtn, &QPushButton::clicked, this, &UserDetailsDlg::onAvatarUpload);
	connect(backBtn, &QPushButton::clicked, this, &UserDetailsDlg::close);
	connect(deleteUserBtn, &QPushButton::clicked, this, [=]
		{
			QJsonObject jobj;
			jobj.insert("lists", QJsonArray({ m_juser.value("user_id") }));

			SHttpClient(URL("/api/user/delete")).debug(true)
				.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
				.json(jobj)
				.fail([=](const QString& msg, int code)
					{

					})
				.success([=](const QByteArray& data)
					{
						emit userDeleted(m_juser);
						this->close();
					}).post();
		});
}

void UserDetailsDlg::setUser(const QJsonObject& juser)
{
	m_juser = juser;
	m_user_id_lab->setText(m_juser["user_id"].toString());
	m_user_name_lab->setText(m_juser["username"].toString());
	m_user_email_lab->setText(m_juser["email"].toString());
	m_user_mobile_lab->setText(m_juser["telephone"].toString());

	onAvatarDownload();
}

void UserDetailsDlg::onAvatarDownload()
{
	SHttpClient(URL("/api/user/avatar")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.param("user_id", m_juser["user_id"].toString())
		.fail([=](const QString& msg, int code)
			{
				//下载失败(没有头像)，显示默认头像
				m_avatar_lab->setPixmap(QPixmap(":/Resource/default_avatar.jpg"));
				m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));
			})
		.success([=](const QByteArray& data)
			{
				if (data.startsWith("{"))
				{
					//{ 开头通常表示返回的是一个JSON对象
					// 意味着脚本请求的资源没有找到或出现错误，应当显示默认头像
					m_avatar_lab->setPixmap(QPixmap(":/Resource/default_avatar.jpg"));
					m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));

				}
				else
				{
					auto img = QImage::fromData(data);
					m_avatar_lab->setPixmap(QPixmap::fromImage(img));
					m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));

				}
			}).get();
}

void UserDetailsDlg::onAvatarUpload()
{
	auto path = sApp->globalConfig()->value("other/select_avatar_path", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	auto file_path = QFileDialog::getOpenFileName(this, "选择头像文件", "", "images(*.jpg;*.jpeg;*.png)");
	//如果没选就直接返回
	if (file_path.isEmpty())return;
	//选了的话就保存到配置文件里（只要路径，不要后面的文件名）
	sApp->globalConfig()->setValue("other/select_avatar_path", QFileInfo(file_path).canonicalPath());
	//上传的头像不能超过3M
	if (QFileInfo(file_path).size() > 3 * 1024 * 1024)
	{
		QMessageBox::warning(this, "上传头像失败", "头像文件大小不能超过3M");
		return;
	}
	QFile file(file_path);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "上传头像失败", "打开头像文件失败：" + file.errorString());
		return;
	}
	auto url = URL("/api/user/avatar?user_id=" + m_juser["user_id"].toString());

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", "Bearer" + sApp->getUserData("user/token").toString().toUtf8());
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	
	QHttpMultiPart* mpart = new QHttpMultiPart(this);
	QHttpPart part;
	part.setHeader(QNetworkRequest::ContentTypeHeader,QString("image/%1").arg(QFileInfo(file_path).suffix().toLower()));
	part.setHeader(QNetworkRequest::ContentDispositionHeader, QString(R"(attachement; name="file"; filename="%1")")
		.arg(QFileInfo(file_path).fileName()));
	part.setBody(file.readAll());
	mpart->append(part);
	auto reply =manager->post(request, mpart);
	connect(reply, &QNetworkReply::finished, [=]()
		{
			if (reply->error() == QNetworkReply::NoError)
			{
				m_avatar_lab->setPixmap(QPixmap(file_path));
				m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));
			}
			else
			{
				m_avatar_lab->setPixmap(QPixmap(":/Resource/default_avatar.jpg"));
				m_avatar_lab->setMask(QRegion(m_avatar_lab->rect(), QRegion::RegionType::Ellipse));
				QMessageBox::warning(this, "上传头像失败", "头像上传失败：" + reply->errorString());
			}
		});



}
