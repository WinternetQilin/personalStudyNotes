#ifndef _SERVER_H_
#define _SERVER_H_

#include<qobject.h>
#include<qwebsocket.h>
#include<qwebsocketserver.h>
#include<qhash.h>

class Server : public QObject
{
	Q_OBJECT
public:
	Server(QObject* parent = nullptr);
	void init();
	bool start(const QHostAddress& address, quint16 port);

protected://slot
	void onNewConnection();
	void onDisconnection();
	void onBinaryMessageReceived(const QByteArray& data);
	void onTextMessageReceived(const QString& data);


private:
	QWebSocketServer* m_server{};
	QHash<QString, QWebSocket*> m_clients;
};

#endif // !_SERVER_H_
