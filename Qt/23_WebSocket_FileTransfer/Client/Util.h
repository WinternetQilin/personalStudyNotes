#ifndef UTIL_H_
#define UTIL_H_

#include<qstring.h>

//传入字节大小，大于1000kb返回"x.MB"，否则返回"x.KB"，大于1000mb返回"x.GB"
QString FitByteDisplay(quint64 bytesSize);

//计算传输速度
QString transformSpeed(quint64 curByteSize, quint64 passedTime);

//计算剩余时间
QString TimeRemaining(quint64 curByteSize, quint64 totalByteSize, quint64 passedTime);


#endif // !UTIL_H_
