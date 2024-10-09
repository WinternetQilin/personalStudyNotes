#ifndef USERDETAILSDLG_H
#define USERDETAILSDLG_H

#include <QWidget>
#include<qjsonobject.h>
#include<qlabel.h>

class UserDetailsDlg : public QWidget
{
    Q_OBJECT

public:
    explicit UserDetailsDlg(QWidget *parent = nullptr);
    void init();
    void setUser(const QJsonObject& juser);
signals:
    void userChanged(const QJsonObject& juser);
    void userDeleted(const QJsonObject& juser);
protected://slots
    void onAvatarDownload();
    void onAvatarUpload();
private:
    QJsonObject m_juser;

    QLabel* m_user_id_lab{};
    QLabel* m_user_name_lab{};
    QLabel* m_user_email_lab{};
    QLabel* m_user_mobile_lab{};
    //用户头像
    QLabel* m_avatar_lab{};
};

#endif // USERDETAILSDLG_H
