#ifndef USERADDDLG_H
#define USERADDDLG_H

#include <QWidget>
#include<qjsonobject.h>
#include<qlabel.h>
#include<qradiobutton.h>
#include<qlineedit.h>

class UserAddDlg : public QWidget
{
    Q_OBJECT

public:
    UserAddDlg(QWidget *parent = nullptr);
    void init();
signals:
    void newUser(const QJsonObject& juser);
private:
    QJsonObject m_juser;

    QLineEdit* m_user_id_edit{};//用户ID输入框
    QLineEdit* m_user_name_edit{};//用户名输入框
    QLineEdit* m_user_mobile_edit{};//用户手机号输入框
    QLineEdit* m_user_email_edit{};//用户邮箱输入框

    QRadioButton* m_def_password_rBtn{};//默认密码单选按钮
    QRadioButton* m_custom_password_rBtn{};//自定义密码单选按钮

    QLineEdit* m_user_password_edit{};//用户密码输入框
    


};

#endif // USERADDDLG_H
