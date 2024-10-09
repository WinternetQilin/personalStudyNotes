#include "MainWindow.h"
#include"SMaskWidget.h"

#include<qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qsplitter.h>

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	init();
	SMaskWidget::instance()->setMainWidget(this);
}

void MainWindow::init()
{
	initMainWindow();
	initUserManagePage();
}

void MainWindow::initMainWindow()
{
	this->resize(800, 600);
	m_treeNavBar = new QTreeWidget;
	m_treeNavBar->setMaximumWidth(200);
	QTreeWidgetItem* item = nullptr;
	//头
	item = new QTreeWidgetItem({ "用户权限管理系统" });
	m_treeNavBar->setHeaderItem(item);
	//每一个菜单
	item = new QTreeWidgetItem(m_treeNavBar, { "用户管理" }, 0);
	m_treeNavBar->addTopLevelItem(item);
	item = new QTreeWidgetItem(m_treeNavBar, { "角色管理" }, 1);
	m_treeNavBar->addTopLevelItem(item);
	item = new QTreeWidgetItem(m_treeNavBar, { "权限管理" }, 2);
	m_treeNavBar->addTopLevelItem(item);


	m_stackedWidget = new QStackedWidget;
	auto hLayout = new QHBoxLayout(this);

	//hLayout->addWidget(m_navBar);
	auto sp = new QSplitter;
	sp->addWidget(m_treeNavBar);
	sp->addWidget(m_stackedWidget);
	hLayout->addWidget(sp);

	//m_treeNavBar
	connect(m_treeNavBar, &QTreeWidget::itemClicked, [=](QTreeWidgetItem* item, int column)
		{

		});
}

void MainWindow::initUserManagePage()
{
	m_userManagePage = new UserManagePage;
	m_stackedWidget->addWidget(m_userManagePage);
}
