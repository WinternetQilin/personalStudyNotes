#ifndef _REMOTEFILEDLG_H_
#define _REMOTEFILEDLG_H_
#include<qwidget.h>
#include<qdir.h>
#include<qstandarditemmodel.h>
#include<qfileiconprovider.h>
#include<qwebsocket.h>
#include<qjsondocument.h>
#include<qjsonobject.h>
#include<qjsonarray.h>
#include<qjsonvalue>
#include<QMenu>
#include<qdesktopservices.h>
#include<qelapsedtimer.h>//经过时间计时器

namespace Ui {
	class RemoteFileDlg;
}

class RemoteFileDlg : public QWidget
{
	Q_OBJECT
public:
	explicit RemoteFileDlg(QWidget* parent = nullptr);
	~RemoteFileDlg();

private:
	void init();
	void start(const QUrl& url);
	void sendJson(const QJsonObject& jobj)
	{
		m_client->sendTextMessage(QJsonDocument(jobj).toJson(QJsonDocument::Compact));
	}
	QJsonObject getFiles(const QString& path);

	void updateLocalFile();
	void localFileBack();
	void setLocalFilePath(const QString& path);

	void updateRemoteFile(const QJsonObject& obj);
	void remoteFileBack();
	void setRemoteFilePath(const QString& path);
	void getRemoteFile();

	//传输文件
	void transfer();
	void sendFile(const QString& filename, const QString& peerSavePath);
	void sendFolder(const QString& folderName, const QString& peerSavePath);
	void sendFileOrFolder(const QString& folderName, const QString& peerSavePath);
	

private://slots
	void onLocalFileTableViewDoubleClicked(const QModelIndex& index);
	void onRemoteFileTableViewDoubleClicked(const QModelIndex& index);

	void onConnected();
	void onDisconnected();
	void onBinaryMessageReceived(const QByteArray& data);
	void onTextMessageReceived(const QString& data);
	
private:
	Ui::RemoteFileDlg* ui;
	QFileIconProvider m_fileIconProvider;

	QDir m_localFileDir;
	QStandardItemModel* m_localFileModel{};

	QDir m_remoteFileDir;
	QStandardItemModel* m_remoteFileModel{};

	QMenu* m_contextMenu;//上下文菜单
	QWebSocket* m_client{};
	//保存复制的文件
	enum MenuType{LocalMenu,RemoteMenu};
	int m_menuType;
	QString m_optionFile;//选中的文件
	int m_optionType{-1};//选中的文件是本地还是远程的type

	QString m_recvFileName;
	quint64 m_recvFileSize{};
	//quint64 m_actualFileSize{};
	QFile* m_recvFile{};

	QElapsedTimer m_passedTimer;
};

#endif // !_REMOTEFILEDLG_H_
