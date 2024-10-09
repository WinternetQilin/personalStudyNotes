/********************************************************************************
** Form generated from reading UI file 'wordeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORDEDITOR_H
#define UI_WORDEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WordEditor
{
public:
    QAction *new_action;
    QAction *open_action;
    QAction *save_action;
    QAction *saveAs_action;
    QAction *options_action;
    QAction *exit_action;
    QAction *undo_action;
    QAction *redo_action;
    QAction *cut_action;
    QAction *copy_action;
    QAction *paste_action;
    QAction *delete_action;
    QAction *findAndReplace_action;
    QAction *picture_action;
    QAction *left_align_action;
    QAction *center_align_action;
    QAction *right_align_action;
    QAction *justify_align_action;
    QAction *bold_action;
    QAction *italics_action;
    QAction *underline_action;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *file_menu;
    QMenu *edit_menu;
    QMenu *insert_menu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *WordEditor)
    {
        if (WordEditor->objectName().isEmpty())
            WordEditor->setObjectName("WordEditor");
        WordEditor->resize(800, 600);
        new_action = new QAction(WordEditor);
        new_action->setObjectName("new_action");
        open_action = new QAction(WordEditor);
        open_action->setObjectName("open_action");
        save_action = new QAction(WordEditor);
        save_action->setObjectName("save_action");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        save_action->setIcon(icon);
        saveAs_action = new QAction(WordEditor);
        saveAs_action->setObjectName("saveAs_action");
        options_action = new QAction(WordEditor);
        options_action->setObjectName("options_action");
        exit_action = new QAction(WordEditor);
        exit_action->setObjectName("exit_action");
        undo_action = new QAction(WordEditor);
        undo_action->setObjectName("undo_action");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        undo_action->setIcon(icon1);
        redo_action = new QAction(WordEditor);
        redo_action->setObjectName("redo_action");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        redo_action->setIcon(icon2);
        cut_action = new QAction(WordEditor);
        cut_action->setObjectName("cut_action");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        cut_action->setIcon(icon3);
        copy_action = new QAction(WordEditor);
        copy_action->setObjectName("copy_action");
        paste_action = new QAction(WordEditor);
        paste_action->setObjectName("paste_action");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        paste_action->setIcon(icon4);
        delete_action = new QAction(WordEditor);
        delete_action->setObjectName("delete_action");
        findAndReplace_action = new QAction(WordEditor);
        findAndReplace_action->setObjectName("findAndReplace_action");
        picture_action = new QAction(WordEditor);
        picture_action->setObjectName("picture_action");
        left_align_action = new QAction(WordEditor);
        left_align_action->setObjectName("left_align_action");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        left_align_action->setIcon(icon5);
        left_align_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        center_align_action = new QAction(WordEditor);
        center_align_action->setObjectName("center_align_action");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/middle.png"), QSize(), QIcon::Normal, QIcon::Off);
        center_align_action->setIcon(icon6);
        center_align_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        right_align_action = new QAction(WordEditor);
        right_align_action->setObjectName("right_align_action");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        right_align_action->setIcon(icon7);
        right_align_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        justify_align_action = new QAction(WordEditor);
        justify_align_action->setObjectName("justify_align_action");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/just.png"), QSize(), QIcon::Normal, QIcon::Off);
        justify_align_action->setIcon(icon8);
        justify_align_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        bold_action = new QAction(WordEditor);
        bold_action->setObjectName("bold_action");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        bold_action->setIcon(icon9);
        bold_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        italics_action = new QAction(WordEditor);
        italics_action->setObjectName("italics_action");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/i.png"), QSize(), QIcon::Normal, QIcon::Off);
        italics_action->setIcon(icon10);
        italics_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        underline_action = new QAction(WordEditor);
        underline_action->setObjectName("underline_action");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        underline_action->setIcon(icon11);
        underline_action->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        centralwidget = new QWidget(WordEditor);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        WordEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WordEditor);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        file_menu = new QMenu(menubar);
        file_menu->setObjectName("file_menu");
        edit_menu = new QMenu(menubar);
        edit_menu->setObjectName("edit_menu");
        insert_menu = new QMenu(menubar);
        insert_menu->setObjectName("insert_menu");
        WordEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(WordEditor);
        statusbar->setObjectName("statusbar");
        WordEditor->setStatusBar(statusbar);
        toolBar = new QToolBar(WordEditor);
        toolBar->setObjectName("toolBar");
        WordEditor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(file_menu->menuAction());
        menubar->addAction(edit_menu->menuAction());
        menubar->addAction(insert_menu->menuAction());
        file_menu->addAction(new_action);
        file_menu->addAction(open_action);
        file_menu->addSeparator();
        file_menu->addAction(save_action);
        file_menu->addAction(saveAs_action);
        file_menu->addSeparator();
        file_menu->addAction(options_action);
        file_menu->addAction(exit_action);
        edit_menu->addAction(undo_action);
        edit_menu->addAction(redo_action);
        edit_menu->addSeparator();
        edit_menu->addAction(cut_action);
        edit_menu->addAction(copy_action);
        edit_menu->addAction(paste_action);
        edit_menu->addAction(delete_action);
        edit_menu->addSeparator();
        edit_menu->addAction(findAndReplace_action);
        insert_menu->addAction(picture_action);
        toolBar->addAction(save_action);
        toolBar->addSeparator();
        toolBar->addAction(undo_action);
        toolBar->addAction(redo_action);
        toolBar->addSeparator();
        toolBar->addAction(cut_action);
        toolBar->addAction(paste_action);
        toolBar->addSeparator();
        toolBar->addAction(left_align_action);
        toolBar->addAction(center_align_action);
        toolBar->addAction(right_align_action);
        toolBar->addAction(justify_align_action);
        toolBar->addSeparator();
        toolBar->addAction(bold_action);
        toolBar->addAction(italics_action);
        toolBar->addAction(underline_action);

        retranslateUi(WordEditor);

        QMetaObject::connectSlotsByName(WordEditor);
    } // setupUi

    void retranslateUi(QMainWindow *WordEditor)
    {
        WordEditor->setWindowTitle(QCoreApplication::translate("WordEditor", "WordEditor", nullptr));
        new_action->setText(QCoreApplication::translate("WordEditor", "\346\226\260\345\273\272", nullptr));
        open_action->setText(QCoreApplication::translate("WordEditor", "\346\211\223\345\274\200", nullptr));
        save_action->setText(QCoreApplication::translate("WordEditor", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(shortcut)
        save_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        saveAs_action->setText(QCoreApplication::translate("WordEditor", "\345\217\246\345\255\230\344\270\272", nullptr));
        options_action->setText(QCoreApplication::translate("WordEditor", "\351\200\211\351\241\271", nullptr));
        exit_action->setText(QCoreApplication::translate("WordEditor", "\351\200\200\345\207\272", nullptr));
        undo_action->setText(QCoreApplication::translate("WordEditor", "\346\222\244\351\224\200", nullptr));
#if QT_CONFIG(shortcut)
        undo_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        redo_action->setText(QCoreApplication::translate("WordEditor", "\351\207\215\345\201\232", nullptr));
        cut_action->setText(QCoreApplication::translate("WordEditor", "\345\211\252\345\210\207", nullptr));
#if QT_CONFIG(shortcut)
        cut_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        copy_action->setText(QCoreApplication::translate("WordEditor", "\345\244\215\345\210\266", nullptr));
#if QT_CONFIG(shortcut)
        copy_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        paste_action->setText(QCoreApplication::translate("WordEditor", "\347\262\230\350\264\264", nullptr));
#if QT_CONFIG(shortcut)
        paste_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        delete_action->setText(QCoreApplication::translate("WordEditor", "\345\210\240\351\231\244", nullptr));
        findAndReplace_action->setText(QCoreApplication::translate("WordEditor", "\346\237\245\346\211\276/\346\233\277\346\215\242", nullptr));
#if QT_CONFIG(shortcut)
        findAndReplace_action->setShortcut(QCoreApplication::translate("WordEditor", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        picture_action->setText(QCoreApplication::translate("WordEditor", "\345\233\276\347\211\207", nullptr));
        left_align_action->setText(QCoreApplication::translate("WordEditor", "\345\267\246\345\257\271\351\275\220", nullptr));
        center_align_action->setText(QCoreApplication::translate("WordEditor", "\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
        right_align_action->setText(QCoreApplication::translate("WordEditor", "\345\217\263\345\257\271\351\275\220", nullptr));
        justify_align_action->setText(QCoreApplication::translate("WordEditor", "\344\270\244\347\253\257\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        justify_align_action->setToolTip(QCoreApplication::translate("WordEditor", "\344\270\244\347\253\257\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        bold_action->setText(QCoreApplication::translate("WordEditor", "\347\262\227\344\275\223", nullptr));
        italics_action->setText(QCoreApplication::translate("WordEditor", "\346\226\234\344\275\223", nullptr));
        underline_action->setText(QCoreApplication::translate("WordEditor", "\344\270\213\345\210\222\347\272\277", nullptr));
        file_menu->setTitle(QCoreApplication::translate("WordEditor", "\346\226\207\344\273\266", nullptr));
        edit_menu->setTitle(QCoreApplication::translate("WordEditor", "\347\274\226\350\276\221", nullptr));
        insert_menu->setTitle(QCoreApplication::translate("WordEditor", "\346\217\222\345\205\245", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("WordEditor", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WordEditor: public Ui_WordEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORDEDITOR_H
