#ifndef USERMANAGEPAGE_H
#define USERMANAGEPAGE_H
#include"UserDetailsDlg.h"
#include"UserAddDlg.h"
#include <QWidget>
#include <QMessageBox>
#include <QStandardItemModel>
#include<qmenu.h>

namespace Ui { class UserManagePage; }

class UserManagePage : public QWidget
{
    Q_OBJECT

public:
    UserManagePage(QWidget *parent = nullptr);
    ~UserManagePage();
    void init();
protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    void onSearch();
    void onBatchEnable();
    void onBatchDisable();
    void setBatchEnable(bool able);
    void onBatchDelete();
    void onExport();

private:
    void parseJson(const QJsonObject& obj);
private:
    Ui::UserManagePage* ui;
    QStandardItemModel* m_model{};

    UserDetailsDlg* m_userDetailsDlg{};
    UserAddDlg* m_userAddDlg{};

    QList<QStandardItem*> ItemsFromJsonObj(const QJsonObject& jobj);

    QMenu* m_importMenu{};
    void initMenu();
    void singleImport();
    void batchImport();

    void readCSVFile(const QString& fileName);
    void readExcelFile(const QString& fileName);
    void writeCSVFile(const QString& fileName);
    void writeExcelFile(const QString& fileName);
};

#endif // USERMANAGEPAGE_H
