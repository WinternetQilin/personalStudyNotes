#include <QCoreApplication>
#include <qrunnable.h>
#include <qthreadpool.h>
#include "SSqlConnectionPool.h"
#include "Server.h"

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QCoreApplication a(argc, argv);

	SSqlConnectionPool::instance()->setDatabaseName("user_privilege_manager_system");
	SSqlConnectionPool::instance()->setUserName("root");
	SSqlConnectionPool::instance()->setPassword("126133");

	Server server;
	

	return a.exec();
}