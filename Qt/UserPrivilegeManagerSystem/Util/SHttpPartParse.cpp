#include "SHttpPartParse.h"
#include <QDebug>


SHttpPartParse::SHttpPartParse(const QByteArray& body)
	: m_body(body)
{
}

bool SHttpPartParse::parse()
{
	//查找空行
	int pos = m_body.indexOf("\r\n\r\n");
	//获取头
	auto header = m_body.mid(0, pos + strlen("\r\n\r\n")).trimmed();
	//拆分头
	auto headers = header.split('\n');
	//获取边界
	auto boundary = headers.at(0).trimmed();

	for (int i = 1; i < headers.size(); i++)
	{
		//拆分键值对
		auto pair = headers.at(i).trimmed().split(':');
		m_headers.insert(pair.first(), pair.last());
	}
	auto it=m_headers.find("Content-Disposition");
	if (it == m_headers.end())return false;

	auto instructs = it.value().split(';');
	instructs.removeFirst();
	for (const auto& instruct : instructs)
	{
		auto kv = instruct.trimmed().split('=');
		const auto& value = kv.last().removeIf([](const char& ch) {return ch == '\"'; });
		if (kv.first() == "name")
		{
			m_name = value;
		}
		else if (kv.first() == "filename")
		{
			m_filename = value;
		}
	}

	auto endPos = m_body.lastIndexOf(boundary);
	m_data = m_body.mid(pos + strlen("\r\n\r\n"), endPos - 2 - pos - strlen("\r\n\r\n"));
	
	//qDebug()<<m_headers;
	return true;
}

QByteArray SHttpPartParse::header(const QByteArray& key)const
{
	return m_headers.value(key);
}
