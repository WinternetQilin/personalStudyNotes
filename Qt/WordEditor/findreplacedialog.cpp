#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"


FindReplaceDialog::FindReplaceDialog(QTextEdit* edit,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindReplaceDialog)
    ,edit(edit)
{
    ui->setupUi(this);

    // connect(ui->findNext_btn,&QPushButton::clicked,this,&FindReplaceDialog::on_findNext_btn_clicked);
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}

void FindReplaceDialog::on_replace_btn_clicked()
{
    auto replaceStr = ui->replact_lineEdit->text();
    if(replaceStr.isEmpty())return;
    auto findStr = ui->find_lineEdit->text();
    if(findStr.isEmpty())return;

    static bool state = false;
    static QTextCursor cursor;
    QTextDocument::FindFlags flags;
    if(ui->matchCase_cb->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if(!state)
        cursor = edit->document()->find(findStr,cursor,flags);//find默认是查找下一个
    if(!cursor.isNull())
    {
        if(state)
        {
            cursor.removeSelectedText();
            cursor.insertText(replaceStr);
        }
        edit->setTextCursor(cursor);
        state=!state;
    }
    else
    {
        cursor.atStart();
    }

}


void FindReplaceDialog::on_replaceAll_btn_clicked()
{
    auto replaceStr = ui->replact_lineEdit->text();
    if(replaceStr.isEmpty())return;
    auto findStr = ui->find_lineEdit->text();
    if(findStr.isEmpty())return;

    QTextDocument::FindFlags flags;
    if(ui->matchCase_cb->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    QTextCursor cursor;
    while(true)
    {
        cursor = edit->document()->find(findStr,cursor,flags);
        if(cursor.isNull())break;
        cursor.removeSelectedText();
        cursor.insertText(replaceStr);
    }
}


void FindReplaceDialog::on_findPrev_btn_clicked()
{
    auto str = ui->find_lineEdit->text();
    if(str.isEmpty())return;
}


void FindReplaceDialog::on_findNext_btn_clicked()
{
    auto str = ui->find_lineEdit->text();
    if(str.isEmpty())return;

    static QTextCursor cursor;
    QTextDocument::FindFlags flags;
    if(ui->matchCase_cb->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    cursor = edit->document()->find(str,cursor,flags);//find默认是查找下一个
    if(!cursor.isNull())
    {
        edit->setTextCursor(cursor);
    }
    else
    {
        cursor.atStart();
    }
}


void FindReplaceDialog::on_close_btn_clicked()
{
    hide();
}

void FindReplaceDialog::showEvent(QShowEvent *event)
{
    ui->find_lineEdit->setText(edit->textCursor().selectedText());
}

