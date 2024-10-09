#ifndef SERVER_H_
#define SERVER_H_
#include<QHttpServer>

class Server
{
public:
	Server();
private:
	QHttpServer m_server;
};

#endif // !SERVER_H_
