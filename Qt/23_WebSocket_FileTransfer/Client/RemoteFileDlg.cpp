#include "RemoteFileDlg.h"
#include "ui_RemoteFileDlg.h"
#include "Util.h"
#include<qdiriterator.h>
#include<qstandardpaths.h>
#include<qlineedit.h>
#include<qwebsocket.h>
#include<qbuffer.h>
#include<qcursor.h>//获取全局坐标
//请求对方文件列表
#define REQUEST_FILE_LIST "request_file_list"
#define RESPONSE_FILE_LIST "response_file_list"

#define Request(type) "request_"##type
#define Response(type) "response_"##type

static QString FileTypeString(const QFileInfo& info);

RemoteFileDlg::RemoteFileDlg(QWidget* parent)
	:QWidget(parent),
	m_contextMenu(new QMenu(this)),
	ui(new Ui::RemoteFileDlg)
{
	ui->setupUi(this);
	init();
	start(QUrl("ws://127.0.0.1:8888"));
}

RemoteFileDlg::~RemoteFileDlg()
{
	delete ui;
	m_client->close();
	delete m_client;
}

void RemoteFileDlg::init()
{
	//设置右键菜单
	m_contextMenu->addAction("从本地资源管理器打开", [=] 
		{
			if (m_menuType == LocalMenu)
			{
				auto index = ui->local_tableView->currentIndex();
				auto filename = m_localFileModel->data(m_localFileModel->index(index.row(), 0), Qt::DisplayRole).toString();
				QDesktopServices::openUrl(QUrl::fromLocalFile(m_localFileDir.canonicalPath() + "/" + filename));
			}
		});
	m_contextMenu->addAction("传输",this,&RemoteFileDlg::transfer);
	m_contextMenu->addAction("复制", [=]
		{
			if (m_menuType == LocalMenu)
			{
				auto idx = ui->local_tableView->currentIndex();
				auto filename = m_localFileModel->data(m_localFileModel->index(idx.row(), 0), Qt::DisplayRole).toString();
				m_optionFile = m_localFileDir.canonicalPath() + "/" + filename;
			}
			else
			{
				auto idx = ui->remote_tableView->currentIndex();
				auto filename = m_remoteFileModel->data(m_remoteFileModel->index(idx.row(), 0), Qt::DisplayRole).toString();
				m_optionFile = m_remoteFileDir.canonicalPath() + "/" + filename;
			}
			m_optionType = m_menuType;
		});
	auto pastAct = m_contextMenu->addAction("粘贴", [=]
		{
			sendFile(m_optionFile, m_remoteFileDir.canonicalPath());
		});
	pastAct->setEnabled(false);
	m_contextMenu->addAction("删除", [=]()
		{
			
			if (m_menuType == RemoteMenu)
			{
				auto idx = ui->remote_tableView->currentIndex();
				auto filename = m_remoteFileModel->data(m_remoteFileModel->index(idx.row(), 0), Qt::DisplayRole).toString();
				sendJson(
					{
						{"type","request_delete"},
						{"fileNamePath",m_remoteFileDir.canonicalPath() + "/" + filename}
					}
				);
			}
			else
			{
				auto idx = ui->local_tableView->currentIndex();
				auto filename = m_localFileModel->data(m_localFileModel->index(idx.row(), 0), Qt::DisplayRole).toString();
				if (QFile::remove(m_localFileDir.canonicalPath() + "/" + filename))
				{
					m_localFileModel->removeRow(idx.row());
				}
			}
			
		});
	m_contextMenu->addAction("重命名");
	m_contextMenu->addAction("新建文件夹");
	m_contextMenu->addAction("全选");

	//=================本地文件===============
	//找到桌面路径
	m_localFileDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	//创建本地文件模型
	m_localFileModel = new QStandardItemModel(this);
	//将模型放入
	ui->local_tableView->setModel(m_localFileModel);
	//取消双击编辑
	ui->local_tableView->setEditTriggers(QTableView::NoEditTriggers);
	//让鼠标点中后直接选择一整行
	ui->local_tableView->setSelectionBehavior(QTableView::SelectionBehavior::SelectRows);
	//可以按住ctrl多选
	ui->local_tableView->setSelectionMode(QTableView::SelectionMode::ContiguousSelection);
	//设置右键菜单
	ui->local_tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	updateLocalFile();

	connect(ui->local_tableView, &QTableView::doubleClicked, this, &RemoteFileDlg::onLocalFileTableViewDoubleClicked);
	connect(ui->local_backBtn, &QPushButton::clicked, this, &RemoteFileDlg::localFileBack);
	connect(ui->local_refreshBtn, &QPushButton::clicked, this, &RemoteFileDlg::updateLocalFile);
	connect(ui->local_newFolderBtn, &QPushButton::clicked, this, [=]
		{
			QString folder = "新建文件夹";
			if (!m_localFileDir.mkdir(folder))
			{
				qDebug() << "创建文件夹失败";
			}
			//updateLocalFile();

			QList<QStandardItem*> item;
			auto file_item = new QStandardItem(folder);
			file_item->setIcon(m_fileIconProvider.icon(QFileIconProvider::IconType::Folder));

			item.append(file_item);
			item.append(new QStandardItem(""));
			item.append(new QStandardItem());
			item.append(new QStandardItem("文件夹"));

			m_localFileModel->appendRow(item);
			ui->local_tableView->scrollToBottom();
			ui->local_tableView->edit(file_item->index());

			auto items = m_localFileModel->findItems(folder, Qt::MatchFlag::MatchFixedString);
			if (!items.isEmpty())
			{
				ui->local_tableView->scrollTo(items.first()->index());
				//这样就可以更改新建文件夹的名字
				ui->local_tableView->edit(items.first()->index());
				//但是只能改模型里的名字，在外面看还是没变
			}

			
		});
	//更改新建文件夹的名字
	connect(m_localFileModel, &QStandardItemModel::itemChanged, [=](QStandardItem* item)
		{
			m_localFileDir.rename("新建文件夹", item->text());
		});
	//combox选择后跳转路径
	connect(ui->local_curPathCmb, &QComboBox::currentIndexChanged, [=]
		{
			this->setLocalFilePath(ui->local_curPathCmb->currentText());
		});
	//combox编辑完成后跳转路径
	connect(ui->local_curPathCmb->lineEdit(), &QLineEdit::returnPressed, [=]
	{
			this->setLocalFilePath(ui->local_curPathCmb->currentText());
	});
	//右键菜单连接槽
	connect(ui->local_tableView, &QTableView::customContextMenuRequested, [=](const QPoint& pos)
		{
			if (LocalMenu == m_optionType)
			{
				pastAct->setEnabled(false);
			}
			else if (!m_optionFile.isEmpty())
			{
				pastAct->setEnabled(true);
			}
			m_menuType = LocalMenu;
			m_contextMenu->popup(QCursor::pos());
		});
	

	//=================远程文件===============
	m_remoteFileDir.setPath(""); 
	m_remoteFileModel = new QStandardItemModel(this);
	ui->remote_tableView->setModel(m_remoteFileModel);
	ui->remote_tableView->setEditTriggers(QTableView::NoEditTriggers);
	ui->remote_tableView->setSelectionBehavior(QTableView::SelectionBehavior::SelectRows);
	ui->remote_tableView->setSelectionMode(QTableView::SelectionMode::ContiguousSelection);
	ui->remote_tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	
	connect(ui->remote_tableView, &QTableView::doubleClicked, this, &RemoteFileDlg::onRemoteFileTableViewDoubleClicked);
	connect(ui->remote_backBtn, &QPushButton::clicked, this, &RemoteFileDlg::remoteFileBack);
	connect(ui->remote_refreshBtn, &QPushButton::clicked, this, &RemoteFileDlg::getRemoteFile);
	connect(ui->remote_newFolderBtn, &QPushButton::clicked, this, [=]
		{
			sendJson({
				{"type","request_mkdir"},
				{"name","新建文件夹"},
				{"path",m_remoteFileDir.canonicalPath()},
				});
			//updateRemoteFile();
			
		});
	connect(m_remoteFileModel, &QStandardItemModel::itemChanged, [=](QStandardItem* item)
		{
			//m_remoteFileDir.rename("新建文件夹", item->text());
			sendJson({
				{"type","request_rename"},
				{"oldName",item->data(Qt::UserRole).toString()},
				{"newName",item->text()},
				{"path",m_remoteFileDir.canonicalPath()}
				});
		});
	connect(ui->remote_curPathCmb, &QComboBox::currentIndexChanged, [=]
		{
			m_remoteFileDir.setPath(ui->remote_curPathCmb->currentText());
			getRemoteFile();
		});
	connect(ui->remote_curPathCmb->lineEdit(), &QLineEdit::returnPressed, [=]
		{
			m_remoteFileDir.setPath(ui->remote_curPathCmb->currentText());
			getRemoteFile();
		});
	connect(ui->remote_tableView, &QTableView::customContextMenuRequested, [=](const QPoint& pos)
		{
			if (RemoteMenu == m_optionType)
			{
				pastAct->setEnabled(false);
			}
			else if(!m_optionFile.isEmpty())
			{
				pastAct->setEnabled(true);
			}
			m_menuType = RemoteMenu;
			m_contextMenu->popup(QCursor::pos());
		});

	//让两个tableview选择互斥
	connect(ui->local_tableView, &QTableView::clicked, [=]()
		{
			ui->remote_tableView->setCurrentIndex(QModelIndex());
		});
	connect(ui->remote_tableView, &QTableView::clicked, [=]()
		{
			ui->local_tableView->setCurrentIndex(QModelIndex());
		});


	//传输文件
	connect(ui->transferBtn, &QPushButton::clicked, this, &RemoteFileDlg::transfer);
}

void RemoteFileDlg::start(const QUrl& url)
{
	if (!m_client)
	{
		m_client = new QWebSocket("c1");
		connect(m_client, &QWebSocket::errorOccurred, [=]()
			{
				qDebug() << url.toString() << "连接失败";
			});
		connect(m_client, &QWebSocket::connected, this, &RemoteFileDlg::onConnected);
		connect(m_client, &QWebSocket::disconnected, this, &RemoteFileDlg::onDisconnected);
		connect(m_client, &QWebSocket::binaryMessageReceived, this, &RemoteFileDlg::onBinaryMessageReceived);
		connect(m_client, &QWebSocket::textMessageReceived, this, &RemoteFileDlg::onTextMessageReceived);
	}
	m_client->open(url);
}

QJsonObject RemoteFileDlg::getFiles(const QString& path)
{
	QJsonArray jFiles;
	QDirIterator iter(path, QDir::NoDotAndDotDot | QDir::AllEntries);
	while (iter.hasNext())
	{
		auto info = iter.nextFileInfo();
		QJsonObject file;
		file.insert("fileName", info.fileName());
		file.insert("fileSize", info.size());
		file.insert("fileModifyTime", info.lastModified().toString("yyyy/MM/dd hh:mm"));
		file.insert("fileType", FileTypeString(info));
		auto icon = m_fileIconProvider.icon(info);
		if (!icon.isNull())
		{
			auto img = icon.pixmap(16).toImage();
			QByteArray bytes;
			QBuffer buf(&bytes);
			img.save(&buf, "ico");
			buf.close();
			file.insert("iconData", QString::fromLatin1(bytes.toBase64()));
		}



		jFiles.append(file);
	}
	QJsonObject jobj;
	jobj.insert("type", RESPONSE_FILE_LIST);
	jobj.insert("data", jFiles);
	jobj.insert("path", path);
	return jobj;
}

void RemoteFileDlg::updateLocalFile()
{
	//更新前先清空就数据
	m_localFileModel->clear();
	//设置当先路径
	auto idx = ui->local_curPathCmb->findText(m_localFileDir.absolutePath());
	if (-1!= idx)
	{
		ui->local_curPathCmb->setCurrentIndex(idx);
	}
	else
	{
		ui->local_curPathCmb->addItem(m_localFileDir.absolutePath());
		ui->local_curPathCmb->setCurrentIndex(ui->local_curPathCmb->count() - 1);
	}

	//ui->local_curPathCmb->addItem(m_localFileDir.absolutePath());
	//ui->local_curPathCmb->setCurrentIndex(ui->local_curPathCmb->count() - 1);

	QDirIterator iter(m_localFileDir.absolutePath(), QDir::NoDotAndDotDot | QDir::AllEntries);
	
	while (iter.hasNext())
	{
		auto info = iter.nextFileInfo();
		QList<QStandardItem*> items;

		auto file_item = new QStandardItem(info.fileName());
		file_item->setIcon(m_fileIconProvider.icon(info));
		items.append(file_item);

		auto fileType = FileTypeString(info);

		if (fileType != "文件夹")items.append(new QStandardItem(FitByteDisplay(info.size())));
		else items.append(new QStandardItem());
		items.append(new QStandardItem(info.fileTime(QFile::FileTime::FileModificationTime).toString("yyyy/MM/dd hh:mm")));
		items.append(new QStandardItem(fileType));

		m_localFileModel->appendRow(items);
	}
}

void RemoteFileDlg::localFileBack()
{
	m_localFileDir.cdUp();
	updateLocalFile();
}

void RemoteFileDlg::setLocalFilePath(const QString& path)
{
	m_localFileDir.setPath(path);
	updateLocalFile();
}

void RemoteFileDlg::updateRemoteFile(const QJsonObject& obj)
{

	//更新前先清空就数据
	m_remoteFileModel->clear();

	auto path = obj.value("path").toString();

	//设置当先路径
	if (-1 == ui->remote_curPathCmb->currentIndex())
	{
		ui->remote_curPathCmb->lineEdit()->setText(path);
		m_remoteFileDir.setPath(path);
	}

	
	auto fileArr = obj["data"].toArray();
	for (int i = 0; i < fileArr.size(); i++)
	{
		auto file = fileArr.at(i).toObject();
		QList<QStandardItem*> items;
		auto file_item = new QStandardItem(file.value("fileName").toString());
		
		QImage img;
		img.loadFromData(QByteArray::fromBase64(file.value("iconData").toString().toLatin1()),"ico");
		
		file_item->setIcon(QPixmap::fromImage(img));
		auto fileType = file.value("fileType").toString();

		items.append(file_item);
		if (fileType != "文件夹")items.append(new QStandardItem(FitByteDisplay(file.value("fileSize").toInteger())));
		else items.append(new QStandardItem());
		items.append(new QStandardItem(file.value("fileModifyTime").toString()));
		items.append(new QStandardItem(fileType));
		
		m_remoteFileModel->appendRow(items);
	}

	
	
}

void RemoteFileDlg::remoteFileBack()
{
	m_remoteFileDir.cdUp();
	getRemoteFile();
}

void RemoteFileDlg::setRemoteFilePath(const QString& path)
{
	m_remoteFileDir.setPath(path);
	//updateRemoteFile();
}

void RemoteFileDlg::getRemoteFile()
{

	if (!m_client || !m_client->isValid())return;
	QJsonObject jobj;
	jobj.insert("type", REQUEST_FILE_LIST);
	jobj.insert("path", m_remoteFileDir.canonicalPath());
	sendJson(jobj);
}

void RemoteFileDlg::transfer()
{
	//判断是谁发给谁

	QModelIndexList local_Rows = ui->local_tableView->selectionModel()->selectedRows();
	QModelIndexList remote_Rows = ui->remote_tableView->selectionModel()->selectedRows();
	qDebug() << local_Rows;
	qDebug() << remote_Rows;

	if (!local_Rows.isEmpty())//local传给remote
	{
		//遍历选中的文件
		for (const auto& index : local_Rows)
		{
			auto fileName = index.data(Qt::DisplayRole).toString();
			
			auto fileType = m_localFileModel->index(index.row(), 1).data(Qt::DisplayRole).toString();
			sendFileOrFolder(m_localFileDir.canonicalPath() + "/" + fileName, m_remoteFileDir.canonicalPath());

		}
	}
	else if (!remote_Rows.isEmpty())//remote传给local
	{
		QJsonArray jarray;
		for (const auto& idx : remote_Rows)
		{
			auto filename = m_remoteFileDir.canonicalPath() + "/" + idx.data(Qt::DisplayRole).toString();
			jarray.append(filename);

		}
		sendJson({
			{"type",Request("get_file_list")},
			{"fileSavePath",m_localFileDir.canonicalPath()},
			{"data",jarray},
			});

	}
	else
	{
		qWarning() << "未选择文件";
	}



}

void RemoteFileDlg::sendFile(const QString& filename, const QString& peerSavePath)
{
	QFileInfo info(filename);

	//判断是文件还是文件夹
	if (info.isFile())//文件
	{
		//给remote发送要传输的文件信息
		sendJson({
			{"type","sendFiles"},
			{"fileName",info.fileName()},
			{"fileSize",info.size()},
			{"filePath",peerSavePath},
			});
		//发送文件数据
		QFile file(info.absoluteFilePath());
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << file.fileName() << " 打开失败： " << file.errorString();
		}
		else
		{
			//如果文件太大就分块发送
			if (file.size() > 1024 * 1024 * 128)
			{
				while (!file.atEnd())
				{
					m_client->sendBinaryMessage(file.read(1024 * 1024 * 128));
				}
			}
			else
			{
				m_client->sendBinaryMessage(file.readAll());

			}
		}

		

	}
}

void RemoteFileDlg::sendFolder(const QString& folderName, const QString& peerSavePath)
{
	QFileInfo info(folderName);
	if (!info.exists() || !info.isDir())return;

	QDirIterator iter(folderName, QDir::NoDotAndDotDot | QDir::AllEntries, QDirIterator::Subdirectories);
	while (iter.hasNext())
	{
		auto curInfo = iter.nextFileInfo();
		if (curInfo.isFile())
		{
			sendFile(curInfo.canonicalFilePath(), peerSavePath+curInfo.canonicalPath().remove(info.canonicalPath()));
		}
	}

}

void RemoteFileDlg::sendFileOrFolder(const QString& fName, const QString& peerSavePath)
{
	QFileInfo info(fName);
	if (info.isFile())
	{
		sendFile(fName, peerSavePath);
	}
	else if (info.isDir())
	{
		sendFolder(fName, peerSavePath);
	}
}

void RemoteFileDlg::onLocalFileTableViewDoubleClicked(const QModelIndex& index)
{
	auto filename = m_localFileModel->data(m_localFileModel->index(index.row(), 0)).toString();
	qDebug() << filename;
	QFileInfo info(m_localFileDir.absolutePath() + "/" + filename);
	if (info.isDir())
	{
		m_localFileDir.cd(filename);
		updateLocalFile();
	}
}

void RemoteFileDlg::onRemoteFileTableViewDoubleClicked(const QModelIndex& index)
{
	auto filename = m_remoteFileModel->data(m_remoteFileModel->index(index.row(), 0)).toString();
	auto fileType = m_remoteFileModel->data(m_remoteFileModel->index(index.row(), 3)).toString();
	qDebug() << filename << fileType;
	if (fileType == "文件夹")
	{
		m_remoteFileDir.cd(filename);
		getRemoteFile();
	}
}

void RemoteFileDlg::onConnected()
{
	qDebug() << "连接成功" << __FUNCTION__;
	getRemoteFile();
}

void RemoteFileDlg::onDisconnected()
{
	qDebug() << "连接断开" << __FUNCTION__;
}

void RemoteFileDlg::onBinaryMessageReceived(const QByteArray& data)
{
	qDebug() << "接收到二进制消息" << __FUNCTION__;
	if (m_recvFile)
	{
		m_recvFile->write(data);

		//显示下载进度
		transformSpeed(m_recvFile->size(), m_passedTimer.elapsed());
		qDebug() << transformSpeed(m_recvFile->size(), m_passedTimer.elapsed()) + " " +
			FitByteDisplay(m_recvFile->size()) + " ,共：" + FitByteDisplay(m_recvFileSize) + " ,预计：" +
			TimeRemaining(m_recvFile->size(), m_recvFileSize, m_passedTimer.elapsed());

		//接收完成
		if (m_recvFile->size() == m_recvFileSize)
		{
			qDebug() << "接收完成" << " " << m_recvFile->fileName();
			m_recvFile->close();
			m_recvFile->deleteLater();
			m_recvFile = nullptr;
			m_recvFileSize = 0;
		}
	}
}

void RemoteFileDlg::onTextMessageReceived(const QString& data)
{
	qDebug() << "接收到文本消息" << __FUNCTION__;

	//还有一个没写：如果点击远程文件夹，要给本地的发消息，更新本地的

	QJsonParseError err;
	auto jdom = QJsonDocument::fromJson(data.toUtf8(),&err);
	if (err.error != QJsonParseError::NoError)
	{
		qWarning() << "json parse error," << err.errorString();
		return;
	}
	//获取消息类型
	auto type = jdom["type"].toString();

	if (type == REQUEST_FILE_LIST)
	{
		auto path = jdom["path"].toString();
		path = path.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) : path;
		sendJson(getFiles(path));
	}
	else if (type == RESPONSE_FILE_LIST)
	{
		updateRemoteFile(jdom.object());
	}
	else if (type == "sendFiles")
	{
		m_recvFileName = jdom["fileName"].toString();
		m_recvFileSize = jdom["fileSize"].toInteger();
		auto recvFilePath = jdom["filePath"].toString();

		QDir dir(recvFilePath);
		if (!dir.exists())
		{
			if (!dir.mkpath(recvFilePath))
			{
				qWarning() << "路径创建失败" << recvFilePath;
				return;
			}
			m_passedTimer.restart();
		}

		m_recvFile = new QFile(recvFilePath + "/" + m_recvFileName);
		if (!m_recvFile->open(QIODevice::WriteOnly | QIODevice::Append))
		{
			qWarning() << recvFilePath << "打开失败：" << m_recvFile->errorString();
		}
	}
	else if (type == "request_mkdir")
	{
		QDir dir(jdom["path"].toString());
		dir.mkdir(jdom["name"].toString());
		sendJson({
			{"type","response_mkdir"},
			{"name",jdom["name"].toString()},
			});
	}
	else if (type == "response_mkdir")
	{
		QList<QStandardItem*> item;
		auto file_item = new QStandardItem(jdom["name"].toString());
		file_item->setIcon(m_fileIconProvider.icon(QFileIconProvider::IconType::Folder));
		file_item->setData(jdom["name"].toString(),Qt::UserRole);

		item.append(file_item);
		item.append(new QStandardItem(""));
		item.append(new QStandardItem());
		item.append(new QStandardItem("文件夹"));

		m_remoteFileModel->appendRow(item);
		ui->remote_tableView->scrollToBottom();
		ui->remote_tableView->edit(file_item->index());
	}
	else if (type == "request_rename")
	{
		QDir dir(jdom["path"].toString());
		dir.rename(jdom["oldName"].toString(), jdom["newName"].toString());

	}
	else if (type == Request("delete"))
	{
		if (QFile::remove(jdom["fileNamePath"].toString()))
		{
			sendJson({
				{"type",Response("delete")},
				{"message","success"}
				});
		}
		else
		{
			sendJson({
				{"type",Response("delete")},
				{"message","failed"}
				});
		}
	}
	else if (type == Response("delete"))
	{
		if (jdom["message"] == "success")
		{
			auto idx = ui->remote_tableView->currentIndex();
			m_remoteFileModel->removeRow(idx.row());
		}
	}
	else if (type == Request("get_file_list"))
	{
		auto jarray = jdom["data"].toArray();
		auto peerSavePath = jdom["fileSavePath"].toString();
		for (size_t i = 0; i < jarray.size(); ++i)
		{
			auto filename = jarray.at(i).toString();
			sendFileOrFolder(filename, peerSavePath);
		}
	}

}

static QString FileTypeString(const QFileInfo& info)
{
	if (info.isAlias()) { return "别名"; }      //mac
	if (info.isBundle()) { return "bundle"; }     //mac
	if (info.isDir()) { return "文件夹"; }
	if (info.isExecutable()) { return "exe"; }
	if (info.isFile()) { return info.suffix(); }
	if (info.isHidden()) { return "隐藏文件"; }
	if (info.isJunction()) { return "lnk"; }
	if (info.isShortcut()) { return "lnk"; }
	if (info.isSymLink()) { return "lnk"; }
	if (info.isSymbolicLink()) { return "lnk"; }
	return "unknown";
}
