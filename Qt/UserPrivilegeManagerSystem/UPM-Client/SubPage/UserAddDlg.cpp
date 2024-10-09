#include "UserAddDlg.h"
#include"SHttpClient.h"
#include"SApp.h"

#include<qboxlayout.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qformlayout.h>

UserAddDlg::UserAddDlg(QWidget* parent)
	:QWidget(parent)
{
	init();
}

void UserAddDlg::init()
{
	m_user_id_edit = new QLineEdit();
	m_user_name_edit = new QLineEdit();
	m_user_mobile_edit = new QLineEdit();
	m_user_email_edit = new QLineEdit();
	m_def_password_rBtn = new QRadioButton("默认密码");
	m_custom_password_rBtn = new QRadioButton("自定义密码");
	m_user_password_edit = new QLineEdit();

	m_def_password_rBtn->setChecked(true);
	m_user_password_edit->setPlaceholderText("请输入自定义密码");
	m_user_password_edit->setDisabled(true);
	//给定一个默认的id
	m_user_id_edit->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));

	//整体的表格布局
	auto flayout = new QFormLayout(this);
	flayout->addRow("<font color='red' size='2'>*</font>用户ID:", m_user_id_edit);
	flayout->addRow("<font color='gray' size='2'>最多64个字符，允许字母、数字</font>", new QLabel);
	flayout->addRow("<font color='red' size='2'>*</font>用户名:", m_user_name_edit);
	flayout->addRow("<font color='gray' size='2'>最多64个字符，允许字母、数字、中文、特殊字符</font>", new QLabel);
	flayout->addRow("<font color='red' size='2'>*</font>手机号码:", m_user_mobile_edit);
	flayout->addRow("<font color='gray' size='2'>11位数字，允许数字、-符号</font>", new QLabel);
	flayout->addRow("邮箱地址:", m_user_email_edit);
	flayout->addRow("<font color='gray' size='2'>最大长度32位，允许字母、数字、@符号</font>", new QLabel);
	//局部横向的默认/自定义密码选择布局
	auto hlayout = new QHBoxLayout();
	hlayout->addWidget(m_def_password_rBtn);
	hlayout->addWidget(m_custom_password_rBtn);
	flayout->addRow("<font color='red' size='2'>*</font>密码:", hlayout);
	flayout->addRow(m_user_password_edit);
	{
		//一行：确定添加和取消添加按钮
		auto btn_hlayout = new QHBoxLayout();
		auto ok_btn = new QPushButton("确定");
		auto cancel_btn = new QPushButton("取消");
		btn_hlayout->addWidget(cancel_btn);
		btn_hlayout->addWidget(ok_btn);
		flayout->addRow(btn_hlayout);
		connect(ok_btn, &QPushButton::clicked, this, [=] {
			m_juser.insert("user_id", m_user_id_edit->text());
			m_juser.insert("username", m_user_name_edit->text());
			m_juser.insert("telephone", m_user_mobile_edit->text());
			m_juser.insert("email", m_user_email_edit->text());
			if (m_def_password_rBtn->isChecked())
			{
				m_juser.insert("password", "123456");
			}
			else
			{
				m_juser.insert("password", m_user_password_edit->text());
			}
			
			SHttpClient(URL("/api/user/create")).debug(true)
				.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
				.json(m_juser)
				.success([=](const QByteArray& data)
					{
						QJsonParseError error;
						auto jdom = QJsonDocument::fromJson(data, &error);
						if (error.error != QJsonParseError::NoError&&jdom["code"].toInt() > 1000)
						{
							qDebug() << "Parse json error:" << error.errorString();
							return;
						}
						else
						{
							emit newUser(m_juser);
						}
					}).post();

			close();
			});
		connect(cancel_btn, &QPushButton::clicked, this, &QWidget::close);
	}
	//整体的表格布局设置成总是换行
	flayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

	//点击自定义密码时让密码输入框可用
	connect(m_custom_password_rBtn, &QRadioButton::clicked, m_user_password_edit, &QLineEdit::setEnabled);
	//点击默认密码时让密码输入框不可用
	connect(m_def_password_rBtn, &QRadioButton::clicked, m_user_password_edit, &QLineEdit::setDisabled);
}
