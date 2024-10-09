#include<QApplication>
#include"Server.h"

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Server server;
	server.start(QHostAddress::Any, 8888);

	return a.exec();
}

#include "main.moc"