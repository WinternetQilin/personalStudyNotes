#include "SSqlConnectionPool.h"
#include<qdatetime.h>
#include<QThread>

SSqlConnectionPool::SSqlConnectionPool()
	:m_databaseType("QMYSQL"),m_maxConnectCount(10),m_waitInterval(100),m_port(3306),m_hostName("localhost")
{
}

SSqlConnectionPool* SSqlConnectionPool::instance()
{
	static SSqlConnectionPool* ins = nullptr;
	if (!ins)
	{
		ins = new SSqlConnectionPool;
	}
	return ins;
}

SSqlConnectionPool::~SSqlConnectionPool()
{
	QMutexLocker<QMutex> locker(&m_mutex);

	for (const auto& con_name : m_usedConnections)
	{
		QSqlDatabase::removeDatabase(con_name);
	}
	for (const auto& con_name : m_unUsedConnections)
	{
		QSqlDatabase::removeDatabase(con_name);
	}
}

QSqlDatabase SSqlConnectionPool::openConnection()
{
	QMutexLocker<QMutex> locker(&m_mutex);//锁

	//如果所有连接都在使用中，没有未使用的
	while (m_maxConnectCount == m_usedConnections.count())
	{
		//等待其他的连接被关闭
		m_waitCond.wait(&m_mutex, m_waitInterval);//上锁
	}

	QString con_name;
	//判断是否能创建新的连接
	if (m_unUsedConnections.count() > 0)
	{
		con_name = m_unUsedConnections.dequeue();
	}
	else if (m_usedConnections.count() < m_maxConnectCount)
	{

		QDateTime currentDateTime = QDateTime::currentDateTime();
		qint64 timestamp = currentDateTime.currentMSecsSinceEpoch();
		con_name = QString("connection-%1").arg(timestamp);
	}
	else
	{
		qWarning() << __FUNCTION__ << " all connection used!";
		return QSqlDatabase();
	}

	auto db = createConnection(con_name);
	if (db.isOpen())
	{
		m_usedConnections.enqueue(con_name);
	}
	return db;

}

void SSqlConnectionPool::closeConnection(QSqlDatabase db)
{
	QMutexLocker<QMutex> locker(&m_mutex);

	QString con_name = db.connectionName();
	if (m_usedConnections.contains(con_name))
	{
		m_usedConnections.removeOne(con_name);
		m_unUsedConnections.enqueue(con_name);
		m_waitCond.wakeOne();//唤醒一个正在等待打开连接的线程（解锁）
	}
}

QSqlDatabase SSqlConnectionPool::createConnection(const QString& con_name)
{
	if (QSqlDatabase::contains(con_name))
	{
		qWarning() << con_name << " connection already exists.";
		auto db = QSqlDatabase::database(con_name);
		if (db.isOpen()) 
		{
			return db;
		}
	}

	QSqlDatabase db = QSqlDatabase::addDatabase(m_databaseType, con_name);
	db.setHostName(m_hostName);
	db.setPort(m_port);
	db.setDatabaseName(m_databaseName);
	db.setUserName(m_userName);
	db.setPassword(m_password);
	if (!db.open())
	{
		qWarning() << __FUNCTION__ << "  error:  " << db.lastError().text();
		return QSqlDatabase();
	}

	return db;

}

void SSqlConnectionPool::releaseConnection(QSqlDatabase db)
{
	QSqlDatabase::removeDatabase(db.connectionName());
}

SConnectionWrap::SConnectionWrap(){}

SConnectionWrap::~SConnectionWrap()
{
	auto pool = SSqlConnectionPool::instance();
	pool->closeConnection(m_db);
}

QSqlDatabase SConnectionWrap::openConnection()
{
	m_db = SSqlConnectionPool::instance()->openConnection();
	return m_db;
}
