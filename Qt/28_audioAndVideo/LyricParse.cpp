#include "LyricParse.h"
#include<qfile.h>
#include<qtextstream.h>
#include<qdebug.h>

LyricParse* LyricParse::instance()
{
	static LyricParse* ins = nullptr;
	if (ins == nullptr)
	{
		ins = new LyricParse;
	}
	return ins;
}

QList<QPair<QString, QString>> LyricParse::getLyric(const QString& music)
{
	auto lyricFile = m_lyricFile.value(music);
	QList<QPair<QString, QString>> lyricList;
	if (lyricFile.isEmpty())
	{
		qWarning() << "未找到歌词：" << music;
		return lyricList;
	}

	QFile file(lyricFile);
	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << "LyricParse::parse error:" << file.errorString();
		return lyricList;
	}
	QTextStream stream(&file);
	while (!stream.atEnd())
	{
		auto line = stream.readLine();
		auto sp = line.split("]");
		lyricList.append({ sp.first(),sp.last() });
	}


	return	lyricList;
}

void LyricParse::addLyric(const QString& music, const QString& lyric)
{
	m_lyricFile.insert(music, lyric);
}

qint64 LyricParse::timeStrToInter(const QString& time)
{
	auto arr = time.split(":");
	int sec = arr.at(0).toInt() * 60 + arr.at(1).toInt();

	return sec;
}
