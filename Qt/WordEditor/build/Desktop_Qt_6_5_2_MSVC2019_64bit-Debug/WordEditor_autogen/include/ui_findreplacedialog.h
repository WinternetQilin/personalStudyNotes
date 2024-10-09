/********************************************************************************
** Form generated from reading UI file 'findreplacedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDREPLACEDIALOG_H
#define UI_FINDREPLACEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindReplaceDialog
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *find_lineEdit;
    QLabel *replace_label;
    QLineEdit *replact_lineEdit;
    QLabel *find_label;
    QCheckBox *matchCase_cb;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *replace_btn;
    QPushButton *replaceAll_btn;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *findPrev_btn;
    QPushButton *findNext_btn;
    QPushButton *close_btn;

    void setupUi(QDialog *FindReplaceDialog)
    {
        if (FindReplaceDialog->objectName().isEmpty())
            FindReplaceDialog->setObjectName("FindReplaceDialog");
        FindReplaceDialog->resize(430, 150);
        FindReplaceDialog->setMinimumSize(QSize(430, 150));
        FindReplaceDialog->setMaximumSize(QSize(430, 150));
        widget = new QWidget(FindReplaceDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 411, 72));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        find_lineEdit = new QLineEdit(widget);
        find_lineEdit->setObjectName("find_lineEdit");

        gridLayout->addWidget(find_lineEdit, 0, 1, 1, 1);

        replace_label = new QLabel(widget);
        replace_label->setObjectName("replace_label");

        gridLayout->addWidget(replace_label, 4, 0, 1, 1);

        replact_lineEdit = new QLineEdit(widget);
        replact_lineEdit->setObjectName("replact_lineEdit");

        gridLayout->addWidget(replact_lineEdit, 4, 1, 1, 1);

        find_label = new QLabel(widget);
        find_label->setObjectName("find_label");

        gridLayout->addWidget(find_label, 0, 0, 1, 1);

        matchCase_cb = new QCheckBox(widget);
        matchCase_cb->setObjectName("matchCase_cb");

        gridLayout->addWidget(matchCase_cb, 1, 1, 1, 1);

        widget1 = new QWidget(FindReplaceDialog);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 90, 158, 26));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        replace_btn = new QPushButton(widget1);
        replace_btn->setObjectName("replace_btn");

        horizontalLayout->addWidget(replace_btn);

        replaceAll_btn = new QPushButton(widget1);
        replaceAll_btn->setObjectName("replaceAll_btn");

        horizontalLayout->addWidget(replaceAll_btn);

        widget2 = new QWidget(FindReplaceDialog);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(180, 120, 239, 26));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        findPrev_btn = new QPushButton(widget2);
        findPrev_btn->setObjectName("findPrev_btn");

        horizontalLayout_2->addWidget(findPrev_btn);

        findNext_btn = new QPushButton(widget2);
        findNext_btn->setObjectName("findNext_btn");
        findNext_btn->setEnabled(true);

        horizontalLayout_2->addWidget(findNext_btn);

        close_btn = new QPushButton(widget2);
        close_btn->setObjectName("close_btn");

        horizontalLayout_2->addWidget(close_btn);


        retranslateUi(FindReplaceDialog);

        QMetaObject::connectSlotsByName(FindReplaceDialog);
    } // setupUi

    void retranslateUi(QDialog *FindReplaceDialog)
    {
        FindReplaceDialog->setWindowTitle(QCoreApplication::translate("FindReplaceDialog", "\346\237\245\346\211\276/\346\233\277\346\215\242", nullptr));
        replace_label->setText(QCoreApplication::translate("FindReplaceDialog", "\346\233\277\346\215\242\344\270\272\357\274\232", nullptr));
        find_label->setText(QCoreApplication::translate("FindReplaceDialog", "\346\237\245\346\211\276\345\206\205\345\256\271\357\274\232", nullptr));
        matchCase_cb->setText(QCoreApplication::translate("FindReplaceDialog", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", nullptr));
        replace_btn->setText(QCoreApplication::translate("FindReplaceDialog", "\346\233\277\346\215\242", nullptr));
        replaceAll_btn->setText(QCoreApplication::translate("FindReplaceDialog", "\345\205\250\351\203\250\346\233\277\346\215\242", nullptr));
        findPrev_btn->setText(QCoreApplication::translate("FindReplaceDialog", "\346\237\245\346\211\276\344\270\212\344\270\200\345\244\204", nullptr));
        findNext_btn->setText(QCoreApplication::translate("FindReplaceDialog", "\346\237\245\346\211\276\344\270\213\344\270\200\345\244\204", nullptr));
        close_btn->setText(QCoreApplication::translate("FindReplaceDialog", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindReplaceDialog: public Ui_FindReplaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDREPLACEDIALOG_H
