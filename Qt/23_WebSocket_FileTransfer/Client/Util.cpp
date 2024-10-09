#include "Util.h"

QString FitByteDisplay(quint64 bytesSize)
{
	QString uint;
	qreal bytes = (qreal)bytesSize;
	if (bytes < 1024)
	{
		uint = " B";
	}
	else if (bytes < 1024 * 1024)
	{
		bytes /= 1024;
		uint = " KB";
	}
	else if (bytes < 1024 * 1024 * 1024)
	{
		bytes /= 1024;
		bytes /= 1024;
		uint = " MB";
	}
	else
	{
		bytes /= 1024;
		bytes /= 1024;
		bytes /= 1024;
		uint = " GB";
	}


	return QString("%1%2").arg(bytes,4,'f',2).arg(uint);
}

QString transformSpeed(quint64 curByteSize, quint64 passedTime)
{
	//计算下载速度：
	//passedTime 单位是ms 1/1000
	//byteSize 单位是byte 1/1024
	//byteSize/elapsedTime=byte/ms 但是我们需要byte/s
	//byteSize/(elapsedTime/1000)=byteSize*1000/elapsedTime
	qreal speed = curByteSize * 1000.0 / passedTime;
	QString unit;
	if (speed < 1024)
	{
		unit = "B/s";
	}
	else if (speed < 1024 * 1024)
	{
		unit = "KB/s";
		speed /= 1024;
	}
	else if (speed < 1024 * 1024 * 1024)
	{
		unit = "MB/s";
		speed /= 1024;
		speed /= 1024;
	}
	else
	{
		unit = "GB/s";
		speed /= 1024;
		speed /= 1024;
		speed /= 1024;
	}

	return QString("%1 %2").arg(speed, 4, 'f', 2).arg(unit);
}

QString TimeRemaining(quint64 curByteSize, quint64 totalByteSize, quint64 passedTime)
{
	//计算剩余未传输大小
	qreal remainBytes = static_cast<qreal>(totalByteSize - curByteSize);
	//计算当前下载速度
	qreal curSpeed = curByteSize * 1000.0 / passedTime;
	//计算预估剩余字节的下载时间
	qreal estimateTime = remainBytes / curSpeed;

	QString uint;
	if (estimateTime < 60)
	{
		uint = "秒";
	}
	else if (estimateTime < 60 * 60)
	{
		uint = "分钟";
		estimateTime /= 60;
	}
	else
	{
		uint = "小时";
		estimateTime /= 60;
		estimateTime /= 60;
	}

	return QString("%1 %2").arg(estimateTime,4,'f',2).arg(uint);
}
