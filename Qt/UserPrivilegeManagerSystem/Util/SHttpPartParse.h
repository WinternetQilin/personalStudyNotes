#ifndef SHTTPPARTPARSE_H
#define SHTTPPARTPARSE_H

#include <QMap>

class SHttpPartParse
{
public:
    SHttpPartParse(const QByteArray& body);
    bool parse();
    QByteArray header(const QByteArray& key) const;
    const QByteArray& name() const { return m_name; };
    const QByteArray& filename() const { return m_filename; };
    const QByteArray& data() const { return m_data; };
private:
    QByteArray m_body;
    QByteArray m_data;
    QMap<QByteArray, QByteArray> m_headers;
    QByteArray m_name;
    QByteArray m_filename;
};

#endif // !
