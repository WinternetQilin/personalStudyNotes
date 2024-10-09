#ifndef WORDEDITOR_H
#define WORDEDITOR_H

#include <QMainWindow>
#include<QToolButton>
#include<QComboBox>
#include<QFontComboBox>
#include<QGraphicsColorizeEffect>
#include<QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class WordEditor;
}
QT_END_NAMESPACE

class WordEditor : public QMainWindow
{
    Q_OBJECT

public:
    WordEditor(QWidget *parent = nullptr);
    ~WordEditor();

public slots:
    //打开
    void openFile();
    //新建
    void newFile();
    //保存
    bool saveFile();
    //另存为
    bool saveAsFile();
    //修改字体样式
    void setTextStyle(int type);
    //修改字体对齐方式
    void setTextAlign(int type);
    //文本编辑
    void textEdit(int type);
    //插入文本
    void insertPicture();

private:
    //是否已保存-返回true表示已保存，返回false表示未保存
    bool whetherSaved();
    //加载文件
    void loadFile(QString pathname);
    //设置当前编辑的文件名
    void setCurFilename(const QString& filename);
    //保存文件功能
    bool saveFile_func();

protected:
    void closeEvent(QCloseEvent* e)override;

private:
    Ui::WordEditor *ui;
    QString m_cur_filename;

    QToolButton* fontColor_toolBtn{};
    QComboBox* fontSize_cbx{};
    QFontComboBox* font_cbx{};
    QGraphicsColorizeEffect* color_effect{};
    QDialog* findReplace_dialog{};
};
#endif // WORDEDITOR_H
