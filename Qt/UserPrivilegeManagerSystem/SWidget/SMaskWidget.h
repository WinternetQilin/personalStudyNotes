#ifndef SMASKWIDGET_H
#define SMASKWIDGET_H

#include <QWidget>

class SMaskWidget : public QWidget
{
    Q_OBJECT
public:
    SMaskWidget(QWidget* parent = nullptr);
    static SMaskWidget* instance();//改成单例模式
    void setMainWidget(QWidget* widget);
    void addDialog(QWidget* dialog);
    void popUp(QWidget* dialog);
protected:
    //重写事件过滤器，使其可以根据m_mainWidget的resize进行resize
    bool eventFilter(QObject* obj, QEvent* ev) override;
    void resizeEvent(QResizeEvent* event) override;
    void onResize();
private:
    QWidget* m_mainWidget{};
    QWidgetSet m_dialogs{};
    QWidget* m_currentDialog{};
};

#endif // SMASKWIDGET_H
