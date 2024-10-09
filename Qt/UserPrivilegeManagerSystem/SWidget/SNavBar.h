#ifndef SNAVBAR_H
#define SNAVBAR_H

#include <QWidget>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qboxlayout.h>
#include <qabstractbutton.h>

class SNavBar : public QWidget
{
    Q_OBJECT
public:
    SNavBar(QWidget* parent = nullptr);

    void addNav(const QString& text, int id=-1);
    void addNav(const QIcon& icon, const QString& text, int id=-1);
    void setNavHeader(const QString& text);

signals:
        void idClicked(int id);
        void buttonClicked(QAbstractButton* button);

private:
    void init();
    QVBoxLayout* m_vlayout{};
    QLabel* m_header{};
    QButtonGroup* m_buttonGroup{};
    int m_lastId{};
};

#endif // SNAVBAR_H
