#ifndef LYRICPARSE_H_
#define LYRICPARSE_H_
#include<qstring.h>
#include<qhash.h>

class LyricParse 
{
public:
	static LyricParse* instance();
	static void parse(QString lyricFile);
	QList<QPair<QString, QString>> getLyric(const QString& music);
	void addLyric(const QString& music, const QString& lyric);
	static qint64 timeStrToInter(const QString& time);

private:
	QHash<QString,QString> m_lyricFile;

};

#endif // !LYRICPARSE_H_
