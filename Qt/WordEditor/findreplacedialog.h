#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>
#include<QTextEdit>

namespace Ui {
class FindReplaceDialog;
}

class FindReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindReplaceDialog(QTextEdit* edit,QWidget *parent = nullptr);
    ~FindReplaceDialog();

private slots:
    void on_replace_btn_clicked();

    void on_replaceAll_btn_clicked();

    void on_findPrev_btn_clicked();

    void on_findNext_btn_clicked();

    void on_close_btn_clicked();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::FindReplaceDialog *ui;
    QTextEdit* edit{};
};

#endif // FINDREPLACEDIALOG_H
