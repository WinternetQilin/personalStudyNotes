#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "UserManagePage.h"

#include <qwidget.h>
#include <qstackedwidget.h>
#include <qtreewidget.h>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	void init();
private:
	void initMainWindow();
	QTreeWidget* m_treeNavBar;
	UserManagePage* m_userManagePage;
	void initUserManagePage();
	QStackedWidget* m_stackedWidget;
};

#endif // MAINWINDOW_H
