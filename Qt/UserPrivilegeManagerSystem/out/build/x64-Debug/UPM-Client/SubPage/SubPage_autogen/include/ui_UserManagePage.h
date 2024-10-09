/********************************************************************************
** Form generated from reading UI file 'UserManagePage.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGEPAGE_H
#define UI_USERMANAGEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManagePage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addUserBtn;
    QPushButton *exportBtn;
    QSpacerItem *horizontalSpacer;
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QTableView *tableView;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *batchEnableBtn;
    QPushButton *batchDisableBtn;
    QPushButton *batchDeleteBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *UserManagePage)
    {
        if (UserManagePage->objectName().isEmpty())
            UserManagePage->setObjectName("UserManagePage");
        UserManagePage->resize(831, 479);
        verticalLayout = new QVBoxLayout(UserManagePage);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(UserManagePage);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addUserBtn = new QPushButton(widget);
        addUserBtn->setObjectName("addUserBtn");

        horizontalLayout_2->addWidget(addUserBtn);

        exportBtn = new QPushButton(widget);
        exportBtn->setObjectName("exportBtn");

        horizontalLayout_2->addWidget(exportBtn);

        horizontalSpacer = new QSpacerItem(505, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        searchEdit = new QLineEdit(widget);
        searchEdit->setObjectName("searchEdit");
        searchEdit->setMinimumSize(QSize(200, 0));
        searchEdit->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(searchEdit);

        searchBtn = new QPushButton(widget);
        searchBtn->setObjectName("searchBtn");

        horizontalLayout_2->addWidget(searchBtn);


        verticalLayout->addWidget(widget);

        tableView = new QTableView(UserManagePage);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        widget_2 = new QWidget(UserManagePage);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        batchEnableBtn = new QPushButton(widget_2);
        batchEnableBtn->setObjectName("batchEnableBtn");

        horizontalLayout->addWidget(batchEnableBtn);

        batchDisableBtn = new QPushButton(widget_2);
        batchDisableBtn->setObjectName("batchDisableBtn");

        horizontalLayout->addWidget(batchDisableBtn);

        batchDeleteBtn = new QPushButton(widget_2);
        batchDeleteBtn->setObjectName("batchDeleteBtn");

        horizontalLayout->addWidget(batchDeleteBtn);

        horizontalSpacer_2 = new QSpacerItem(549, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(UserManagePage);

        QMetaObject::connectSlotsByName(UserManagePage);
    } // setupUi

    void retranslateUi(QWidget *UserManagePage)
    {
        UserManagePage->setWindowTitle(QCoreApplication::translate("UserManagePage", "Form", nullptr));
        addUserBtn->setText(QCoreApplication::translate("UserManagePage", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        exportBtn->setText(QCoreApplication::translate("UserManagePage", "\345\257\274\345\207\272\350\241\250\346\240\274", nullptr));
        searchEdit->setPlaceholderText(QCoreApplication::translate("UserManagePage", "\350\276\223\345\205\245ID/\347\224\250\346\210\267\345\220\215/\346\211\213\346\234\272\345\217\267/\351\202\256\347\256\261", nullptr));
        searchBtn->setText(QCoreApplication::translate("UserManagePage", "\346\220\234\347\264\242", nullptr));
        batchEnableBtn->setText(QCoreApplication::translate("UserManagePage", "\346\211\271\351\207\217\345\220\257\347\224\250", nullptr));
        batchDisableBtn->setText(QCoreApplication::translate("UserManagePage", "\346\211\271\351\207\217\347\246\201\347\224\250", nullptr));
        batchDeleteBtn->setText(QCoreApplication::translate("UserManagePage", "\346\211\271\351\207\217\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManagePage: public Ui_UserManagePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEPAGE_H
