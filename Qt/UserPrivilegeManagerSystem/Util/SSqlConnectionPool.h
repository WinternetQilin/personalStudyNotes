#ifndef SSQLCONNECTIONPOOL_H_
#define SSQLCONNECTIONPOOL_H_

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlRecord>
#include<qqueue>
#include<qmutex>//互斥量
#include<qmutexlocker>//自动加锁
#include<qwaitcondition>//等待情况



class SSqlConnectionPool
{
	SSqlConnectionPool();
public:
	static SSqlConnectionPool* instance();//使用单例模式
	~SSqlConnectionPool();

	QSqlDatabase openConnection();
	void closeConnection(QSqlDatabase db);//隐式共享

	void setHoseName(const QString& hostName) { m_hostName = hostName; }
	void setPort(quint16 port) { m_port = port; }
	void setDatabaseName(const QString& dbn) { m_databaseName = dbn; }
	void setUserName(const QString& uname) { m_userName = uname; }
	void setPassword(const QString& pwd) { m_password = pwd; }
	void setDatabaseType(const QString& type) { m_databaseType = type; }
	void setMaxConnectCount(quint32 count) { m_maxConnectCount = count; }
private:
	QSqlDatabase createConnection(const QString& con_name);
	void releaseConnection(QSqlDatabase db);

	quint16 m_port;//端口号
	QString m_hostName;//主机名
	QString m_databaseName;
	QString m_userName;
	QString m_password;

	QString m_databaseType;//链接的数据库类型


	QMutex m_mutex;//互斥量
	QWaitCondition m_waitCond;//条件
	quint32 m_maxConnectCount;//最大连接数量
	quint32 m_waitInterval;//等待间隔
	QQueue<QString> m_usedConnections;//已经使用了的连接名
	QQueue<QString> m_unUsedConnections;//没有使用的连接名

};

class SConnectionWrap
{
public:
	SConnectionWrap();
	~SConnectionWrap();
	QSqlDatabase openConnection();
private:
	QSqlDatabase m_db;
};



#endif // !SSQLCONNECTIONPOOL
