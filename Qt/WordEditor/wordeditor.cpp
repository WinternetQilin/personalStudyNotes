#include "wordeditor.h"
#include "./ui_wordeditor.h"
#include"findreplacedialog.h"

#include<QFileDialog>
#include<QFile>
#include<QStandardPaths>
#include<QDir>
#include<QMessageBox>
#include<QTextStream>
#include<QSaveFile>
#include<QColorDialog>
#include<QFontDatabase>
#include<QCloseEvent>

WordEditor::WordEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WordEditor)
    ,color_effect(new QGraphicsColorizeEffect(this))
    ,fontColor_toolBtn(new QToolButton(this))
    ,font_cbx(new QFontComboBox(this))
    ,fontSize_cbx(new QComboBox(this))
{
    ui->setupUi(this);
    resize(1280,720);

    setWindowTitle(QString());
    setCurFilename(QString());
    statusBar()->showMessage("准备就绪",2000);

    //在工具栏增加修改字体颜色按钮
    color_effect->setColor(Qt::black);
    fontColor_toolBtn->setIcon(QIcon("://icons/textColor.png"));
    ui->toolBar->addWidget(fontColor_toolBtn);
    fontColor_toolBtn->setGraphicsEffect(color_effect);

    //添加一个分隔符
    ui->toolBar->addSeparator();

    //在工具栏增加修改字体样式cbx
    ui->toolBar->addWidget(font_cbx);

    //字体大小
    auto list = QFontDatabase::standardSizes();
    for(auto i : list)
        fontSize_cbx->addItem(QString::number(i));

    QFont curFont = font_cbx->currentFont();
    fontSize_cbx->setCurrentText(QString::number(curFont.pointSize()));
    ui->toolBar->addWidget(fontSize_cbx);

    //字体颜色
    connect(fontColor_toolBtn,&QToolButton::clicked,[=]()
            {
                setTextStyle(3);
            });
    //字体样式
    connect(font_cbx,&QFontComboBox::currentFontChanged,[=]()
            {
                setTextStyle(5);
            });
    //字体大小
    connect(fontSize_cbx,&QComboBox::currentIndexChanged,[=]()
            {
                setTextStyle(4);
            });
    //文本框内容变动
    connect(ui->textEdit->document(),&QTextDocument::contentsChanged,this,[=]()
            {
                setWindowModified(ui->textEdit->document()->isModified());
            });
    //文件菜单
    connect(ui->open_action,&QAction::triggered,this,&WordEditor::openFile);
    connect(ui->new_action,&QAction::triggered,this,&WordEditor::newFile);
    connect(ui->save_action,&QAction::triggered,this,&WordEditor::saveFile);
    connect(ui->saveAs_action,&QAction::triggered,this,&WordEditor::saveAsFile);
    //字体样式
    connect(ui->bold_action,&QAction::triggered,this,[=](){setTextStyle(0);});
    connect(ui->italics_action,&QAction::triggered,this,[=](){setTextStyle(1);});
    connect(ui->underline_action,&QAction::triggered,this,[=](){setTextStyle(2);});
    //字体对齐
    connect(ui->left_align_action,&QAction::triggered,this,[=](){setTextAlign(0);});
    connect(ui->center_align_action,&QAction::triggered,this,[=](){setTextAlign(1);});
    connect(ui->right_align_action,&QAction::triggered,this,[=](){setTextAlign(2);});
    connect(ui->justify_align_action,&QAction::triggered,this,[=](){setTextAlign(3);});
    //文本编辑
    connect(ui->undo_action,&QAction::triggered,this,[=](){textEdit(0);});
    connect(ui->redo_action,&QAction::triggered,this,[=](){textEdit(1);});
    connect(ui->cut_action,&QAction::triggered,this,[=](){textEdit(2);});
    connect(ui->copy_action,&QAction::triggered,this,[=](){textEdit(3);});
    connect(ui->paste_action,&QAction::triggered,this,[=](){textEdit(4);});
    connect(ui->delete_action,&QAction::triggered,this,[=](){textEdit(5);});
    connect(ui->findAndReplace_action,&QAction::triggered,this,[=](){textEdit(6);});
    //插入图片
    connect(ui->picture_action,&QAction::triggered,this,&WordEditor::insertPicture);
}

WordEditor::~WordEditor()
{
    delete ui;
}

void WordEditor::openFile()
{
    //若编辑中的文档未保存
    if(!whetherSaved())return;

    //获取系统桌面的标准地址
    QString desktopPath = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first();

    //如果获取失败就打开程序当前目录
    desktopPath = desktopPath.isEmpty()?QDir::currentPath():desktopPath;

    QString pathname = QFileDialog::getOpenFileName(this,"打开文档",desktopPath,"document (*.txt *.docx);;All (*)");
    //取消选择的情况
    if(pathname.isEmpty())return;

    loadFile(pathname);
}

void WordEditor::newFile()
{
    if(!whetherSaved())return;

    ui->textEdit->clear();
    setCurFilename(QString());
    statusBar()->showMessage("新建成功",2000);
}

bool WordEditor::saveFile()
{
    if(m_cur_filename.isEmpty())
    {
        return saveAsFile();
    }
    return saveFile_func();
}

bool WordEditor::saveAsFile()
{
    QString desktopPath = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first();
    auto pathname = QFileDialog::getSaveFileName(this,"另存为",desktopPath,"Document files (*.docx);;Text files (*.txt);;All files (*.*)");
    // qDebug()<<pathname;
    if(pathname.isEmpty())return false;

    setCurFilename(pathname);
    return saveFile_func();
}

bool WordEditor::whetherSaved()
{
    //未修改返回true
    if(!ui->textEdit->document()->isModified())return true;

    //修改过就弹出消息提示框询问是否保存
    auto btn = QMessageBox::warning(this,"警告","文件未保存！",QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);
    switch(btn)
    {
    case QMessageBox::Save:
        return saveFile();
    case QMessageBox::No:
        return true;
    case QMessageBox::Cancel:
        return false;
    }
}

void WordEditor::loadFile(QString pathname)
{
    QFile file(pathname);
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this,"错误","文件打开失败");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->clear();
    ui->textEdit->insertHtml(in.readAll());
    //对文本框来说加载进来也算有修改
    //但是对用户来说只是加载文件，应该不算修改
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);

    setCurFilename(file.fileName());

}

void WordEditor::setCurFilename(const QString &filename)
{
    if(filename.isEmpty())
    {
        setWindowFilePath("未命名");
        m_cur_filename=QString();
    }
    else if(filename == m_cur_filename)
    {
        return;
    }
    else
    {
        setWindowFilePath(filename);
        m_cur_filename = filename;
    }

}

bool WordEditor::saveFile_func()
{
    QSaveFile sf(m_cur_filename);
    if(sf.open(QSaveFile::WriteOnly|QSaveFile::Text))
    {
        QTextStream out(&sf);
        out<<ui->textEdit->toHtml();

        if(!sf.commit())
        {
            QMessageBox::critical(this,"错误","保存失败");
            return false;
        }
    }
    setCurFilename(m_cur_filename);
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    statusBar()->showMessage("保存成功",2000);
    return true;
}

void WordEditor::closeEvent(QCloseEvent *e)
{
    if(whetherSaved())return;

    e->ignore();
}

void WordEditor::setTextStyle(int type)
{
    //获取光标框选的字符段
    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.isNull())return;
    //获取字符段的字体样式
    QFont font = cursor.charFormat().font();
    QTextCharFormat format;
    switch(type)
    {
    case 0://加粗
        font.setBold(!font.bold());
        break;
    case 1://斜体
        font.setItalic(!font.italic());
        break;
    case 2://下划线
        font.setUnderline(!font.underline());
        break;
    case 4://字体大小
        font.setPointSize(fontSize_cbx->currentText().toInt());
        break;
    case 5://字体样式
        QFont oldFont = font;
        // QTextCharFormat oldformat = format;
        font.setFamily(font_cbx->currentFont().family());
        //设置完字体后，原来的字体大小、粗体、斜体等样式会失效
        //所以要再设置一遍
        font.setPointSize(oldFont.pointSize());
        font.setBold(oldFont.bold());
        font.setItalic(oldFont.italic());
        font.setUnderline(oldFont.underline());
        // format.setForeground(oldformat.foreground());
        break;
    }
    format.setFont(font);
    //字体颜色
    if(type==3)
    {
        QColor c = QColorDialog::getColor(Qt::black,this,"选择颜色");
        if(c.isValid())
        {
            format.setForeground(c);
            color_effect->setColor(c);
        }
    }

    if(!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.setCharFormat(format);
}

void WordEditor::setTextAlign(int type)
{
    QTextBlockFormat format;
    switch(type)
    {
    case 0://左对齐
        format.setAlignment(Qt::AlignLeft);
        break;
    case 1://居中对齐
        format.setAlignment(Qt::AlignCenter);
        break;
    case 2://右对齐
        format.setAlignment(Qt::AlignRight);
        break;
    case 3://两端对齐
        format.setAlignment(Qt::AlignJustify);
        break;
    }
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeBlockFormat(format);
}

void WordEditor::textEdit(int type)
{
    switch(type)
    {
    case 0://撤销
        ui->textEdit->undo();
        break;
    case 1://重做
        ui->textEdit->redo();
        break;
    case 2://剪切
        ui->textEdit->cut();
        break;
    case 3://复制
        ui->textEdit->copy();
        break;
    case 4://粘贴
        ui->textEdit->paste();
        break;
    case 5://删除
        ui->textEdit->deleteLater();
        break;
    case 6://查找替换
        if(!findReplace_dialog)findReplace_dialog = new FindReplaceDialog(ui->textEdit,this);
        findReplace_dialog->show();
        break;
    }
}

void WordEditor::insertPicture()
{
    auto pathname = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),"Images (*.png *.jpg *.jpeg *.gif)");
    if(pathname.isEmpty())return;

    QImage img(pathname);
    ui->textEdit->document()->addResource(QTextDocument::ImageResource,QUrl::fromLocalFile(pathname),QVariant(img));

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat format;
    format.setWidth(img.width());
    format.setHeight(img.height());
    format.setName(pathname);
    cursor.insertImage(format);
}
