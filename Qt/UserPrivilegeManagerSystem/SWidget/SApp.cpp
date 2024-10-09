#include "SApp.h"
#include <qfile.h>

SApp::SApp(int& argc, char** argv)
	: QApplication(argc, argv)
{
	initGlobalConfig();
}

void SApp::initGlobalConfig()
{
	const char* configFilename = "config.ini";
	bool isExists = QFile::exists(configFilename);

	//打开配置文件
	m_globalConfig = new SConfigFile(configFilename);
	Q_ASSERT(m_globalConfig!= nullptr,__FUNCTION__,"Failed to create global config file");
	if (!m_globalConfig->isOpen())
	{
		qWarning() << "Failed to open global config file" << configFilename;
		return;
	}

	//如果不存在，则创建默认配置文件
	if (!isExists)
	{
		globalConfig()->setValue("General/Language", "zh_CN");
		globalConfig()->setValue("host/host", "127.0.0.1:8888");
	}
}

void SApp::setUserData(const QString& key, const QVariant& data)
{
	auto it = m_userData.find(key);
	if (it!= m_userData.end())
		qWarning() << "User data already exists, key:" << key;
	m_userData.insert(key, data);
}

QVariant SApp::getUserData(const QString& key)
{
	auto it = m_userData.find(key);
	if (it == m_userData.end())
	{
		qWarning() << "User data not found, key:" << key;
		return QVariant();
	}

	return m_userData.value(key);
}
