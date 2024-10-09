#include "SConfigFile.h"

SConfigFile::SConfigFile(const QString& filename)
	:m_settings(filename, QSettings::IniFormat)
{
}

void SConfigFile::setValue(QAnyStringView key, const QVariant& value)
{
	m_settings.setValue(key, value);
}

QVariant SConfigFile::value(QAnyStringView key) const
{
	return value(key, QVariant());
}

QVariant SConfigFile::value(QAnyStringView key, const QVariant& defaultValue) const
{
#ifdef _DEBUG
	auto v = m_settings.value(key);
	if (!v.isValid())
	{
		qWarning() << key.toString() << " Not Found in Config File";
		return defaultValue;
	}
#endif

	return m_settings.value(key, defaultValue);
}

void SConfigFile::removeValue(QAnyStringView key)
{
	m_settings.remove(key);
}
