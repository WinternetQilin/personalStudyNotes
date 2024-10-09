#include "UserManagePage.h"
#include "UserManagePage.h"
#include "UserManagePage.h"
#include "UserManagePage.h"
#include "ui_UserManagePage.h"
#include "SMaskWidget.h"
#include "SHttpClient.h"
#include "SApp.h"
#include"xlsxdocument.h"//文档
#include"xlsxworkbook.h"//工作簿
#include "xlsxworksheet.h"//工作表

#include <qpushbutton.h>
#include<qlineedit.h>
#include <qstandarditemmodel.h>
#include<qtableview.h>
#include<QFileDialog>
#include<qtextstream.h>

UserManagePage::UserManagePage(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UserManagePage)
	, m_model(new QStandardItemModel(this))
{
	ui->setupUi(this);
	init();
}

UserManagePage::~UserManagePage()
{
	delete ui;
}

void UserManagePage::init()
{
	initMenu();

	//表格
	ui->tableView->setModel(m_model);

	//初始化表格
	onSearch();

	//搜索框
	connect(ui->searchBtn, &QPushButton::clicked, this, &UserManagePage::onSearch);
	connect(ui->searchEdit, &QLineEdit::returnPressed, this, &UserManagePage::onSearch);
	connect(ui->searchEdit, &QLineEdit::textChanged, [=](const QString& text)
		{
			if (text.trimmed().isEmpty())
			{
				onSearch();
			}
		});
	//批量操作
	connect(ui->batchEnableBtn, &QPushButton::clicked, this, &UserManagePage::onBatchEnable);
	connect(ui->batchDisableBtn, &QPushButton::clicked, this, &UserManagePage::onBatchDisable);
	connect(ui->batchDeleteBtn, &QPushButton::clicked, this, &UserManagePage::onBatchDelete);
	//双击行
	connect(ui->tableView, &QTableView::doubleClicked, [=](const QModelIndex& index)
		{
			qDebug() << index.row() << "," << index.column();
			if (!m_userDetailsDlg)
			{
				m_userDetailsDlg = new UserDetailsDlg(this);
				m_userDetailsDlg->resize(this->size());
				connect(m_userDetailsDlg, &UserDetailsDlg::userChanged, [=](const QJsonObject& juser)
					{
						m_model->item(index.row(), 0)->setText(juser.value("user_id").toString());
						m_model->item(index.row(), 1)->setText(juser.value("username").toString());
						m_model->item(index.row(), 2)->setText(juser.value("gender").toString() == "1" ? "男" : (juser.value("gender").toString() == "2" ? "女" : "未知"));
						m_model->item(index.row(), 3)->setText(juser.value("telephone").toString());
						m_model->item(index.row(), 4)->setText(juser.value("email").toString());
						//m_model->item(index.row(), 5)->setText(juser.value("isEnable").toString() == "1" ? "启用" : "禁用");
						m_model->item(index.row(), 5)->setData(juser.value("isEnable").toInt(), Qt::UserRole);
					});
				connect(m_userDetailsDlg, &UserDetailsDlg::userDeleted, [=](const QJsonObject& juser)
					{
						auto items = m_model->findItems(juser.value("user_id").toString(), Qt::MatchFixedString, 0);
						if (!items.isEmpty())
						{
							auto row = items.first()->row();
							m_model->removeRow(row);
							//qDebug() << "========================row: " << row;
						}
						else
						{
							//qDebug() << "========================user not found";
						}
					});
			}
			QJsonObject juser;
			juser.insert("user_id", m_model->item(index.row(), 0)->text());
			juser.insert("username", m_model->item(index.row(), 1)->text());
			juser.insert("gender", m_model->item(index.row(), 2)->text() == "男" ? 1 : (m_model->item(index.row(), 2)->text() == "女" ? 2 : 0));
			juser.insert("telephone", m_model->item(index.row(), 3)->text());
			juser.insert("email", m_model->item(index.row(), 4)->text());
			juser.insert("isEnable", m_model->item(index.row(), 5)->data(Qt::UserRole).toInt());
			qDebug() << juser;
			m_userDetailsDlg->setUser(juser);
			m_userDetailsDlg->show();
		});
	//添加用户按钮,在initmenu里

	//导出按钮
	connect(ui->exportBtn, &QPushButton::clicked, this, &UserManagePage::onExport);
}

void UserManagePage::resizeEvent(QResizeEvent* event)
{
	if (m_userDetailsDlg)
	{
		m_userDetailsDlg->resize(this->size());
	}
}

void UserManagePage::onSearch()
{
	QVariantMap params;
	params.insert("isDeleted", false);

	auto filter = ui->searchEdit->text().trimmed();
	if (!filter.isEmpty())
	{
		params.insert("query", filter);
	}

	SHttpClient(URL("/api/user/list")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.params(params)
		.success([=](const QByteArray& data)
			{
				QJsonParseError error;
				auto jdom = QJsonDocument::fromJson(data, &error);
				if (error.error != QJsonParseError::NoError)
				{
					qDebug() << "Parse json error:" << error.errorString();
					return;
				}
				parseJson(jdom.object());

			}).get();

}

void UserManagePage::onBatchEnable()
{
	setBatchEnable(true);
}

void UserManagePage::onBatchDisable()
{
	setBatchEnable(false);
}

void UserManagePage::setBatchEnable(bool able)
{
	QJsonObject jobj;
	QJsonArray jarr;
	//判断有哪些行被选中
	for (size_t i = 0; i < m_model->rowCount(); i++)
	{
		auto item = m_model->item(i, 0);
		if (item && item->checkState() == Qt::Checked)
		{
			QJsonObject	filterObj;
			filterObj.insert("user_id", item->text());
			QJsonObject updateObj;
			updateObj.insert("isEnable", able ? 1 : 0);
			QJsonObject recObj;
			recObj.insert("filter", filterObj);
			recObj.insert("update", updateObj);
			jarr.append(recObj);
		}
	}
	jobj.insert("lists", jarr);
	SHttpClient(URL("/api/user/batch_alter")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.json(jobj)
		.fail([=](const QString& msg, int code)
			{

			})
		.success([=](const QByteArray& data)
			{
				onSearch();
				/*QJsonParseError error;
				auto jdom = QJsonDocument::fromJson(data, &error);
				if (error.error != QJsonParseError::NoError)
				{
					qDebug() << "Parse json error:" << error.errorString();
					return;
				}
				parseJson(jdom.object());*/
			}).post();
}

void UserManagePage::onBatchDelete()
{
	QJsonObject jobj;
	QJsonArray jarr;
	//判断有哪些行被选中
	for (size_t i = 0; i < m_model->rowCount(); i++)
	{
		auto item = m_model->item(i, 0);
		if (item && item->checkState() == Qt::Checked)
		{
			jarr.append(item->text());
		}
	}
	jobj.insert("lists", jarr);

	SHttpClient(URL("/api/user/delete")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.json(jobj)
		.fail([=](const QString& msg, int code)
			{

			})
		.success([=](const QByteArray& data)
			{
				onSearch();
				/*QJsonParseError error;
				auto jdom = QJsonDocument::fromJson(data, &error);
				if (error.error != QJsonParseError::NoError)
				{
					qDebug() << "Parse json error:" << error.errorString();
					return;
				}
				parseJson(jdom.object());*/
			}).post();
}

void UserManagePage::onExport()
{
	auto filename = QFileDialog::getSaveFileName(this, "导出用户信息", "./undefined.csv", "csv(*.csv);;Excel Files (*.xlsx);;All Files (*.*)");
	if (filename.isEmpty())return;

	auto extra = QFileInfo(filename).suffix().toLower();
	if (extra == "csv")
	{
		writeCSVFile(filename);
	}
	else if (extra == "xlsx")
	{
		writeExcelFile(filename);
	}

}

void UserManagePage::parseJson(const QJsonObject& obj)
{
	m_model->clear();
	QStringList headers = { "用户ID", "用户名", "性别", "手机号", "邮箱", "账号状态" };
	m_model->setHorizontalHeaderLabels(headers);

	auto jarr = obj.value("data").toObject().value("lists").toArray();
	for (int i = 0; i < jarr.size(); i++)
	{
		//QList<QStandardItem*> items;
		//auto juser = jarr.at(i).toObject();
		//auto gender = juser.value("gender").toInteger();
		////items.append(new QStandardItem(juser.value("id").toVariant().toString()));
		//QStandardItem* item = new QStandardItem(juser.value("user_id").toVariant().toString());
		//item->setCheckable(true);
		//items.append(item);
		//items.append(new QStandardItem(juser.value("username").toVariant().toString()));
		//items.append(new QStandardItem(gender == 0 ? "未知" : (gender == 1 ? "男" : "女")));
		//items.append(new QStandardItem(juser.value("telephone").toVariant().toString()));
		//items.append(new QStandardItem(juser.value("email").toVariant().toString()));
		//auto isEnable = juser.value("isEnable").toInteger();
		//item = new QStandardItem(isEnable == 1 ? "启用" : "禁用");
		//item->setData(isEnable, Qt::UserRole);
		//items.append(item);

		m_model->appendRow(ItemsFromJsonObj(jarr.at(i).toObject()));
	}
}

QList<QStandardItem*> UserManagePage::ItemsFromJsonObj(const QJsonObject& jobj)
{
	QList<QStandardItem*> items;
	auto gender = jobj.value("gender").toInteger();

	QStandardItem* item = new QStandardItem(jobj.value("user_id").toVariant().toString());
	item->setCheckable(true);
	items.append(item);
	items.append(new QStandardItem(jobj.value("username").toVariant().toString()));
	items.append(new QStandardItem(gender == 0 ? "未知" : (gender == 1 ? "男" : "女")));
	items.append(new QStandardItem(jobj.value("telephone").toVariant().toString()));
	items.append(new QStandardItem(jobj.value("email").toVariant().toString()));

	auto isEnable = jobj.value("isEnable").toInteger();
	item = new QStandardItem(isEnable == 1 ? "启用" : "禁用");
	item->setData(isEnable, Qt::UserRole);
	items.append(item);

	return items;
}

void UserManagePage::initMenu()
{
	m_importMenu = new QMenu(this);
	ui->addUserBtn->setMenu(m_importMenu);
	m_importMenu->addAction("单个导入", this, &UserManagePage::singleImport);
	m_importMenu->addAction("批量导入", this, &UserManagePage::batchImport);
}

void UserManagePage::singleImport()
{
	if (!m_userAddDlg)
	{
		m_userAddDlg = new UserAddDlg;
		connect(m_userAddDlg, &UserAddDlg::newUser, [=](const QJsonObject& juser)
			{
				//封装后一步搞定
				m_model->insertRow(0, ItemsFromJsonObj(juser));
				m_userAddDlg->close();
			});

	}
	SMaskWidget::instance()->popUp(m_userAddDlg);
}

void UserManagePage::batchImport()
{
	auto filename = QFileDialog::getOpenFileName(this, "选择批量导入文件", "./", "Excel Files (*.xlsx *.csv)");
	if (filename.isEmpty())
	{
		return;
	}
	//判断是什么类型的文件
	auto extraName = QFileInfo(filename).suffix().toLower();
	if (extraName == "csv")
	{
		readCSVFile(filename);
	}
	else if (extraName == "xls" || extraName == "xlsx")
	{
		readExcelFile(filename);
	}
}

void UserManagePage::readCSVFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << fileName << ": open file error:" << file.errorString();
		return;
	}
	QTextStream stream(&file);
	//不管是不是UTF-8的格式，都先转成系统编码（UTF-8)再处理
	stream.setEncoding(QStringConverter::System);
	auto headers = stream.readLine().split(",");
	qDebug() << headers;
	QJsonArray jarr;
	//工号0 姓名1 性别2 手机号码3
	while (!stream.atEnd())
	{
		auto line = stream.readLine().split(",");
		QJsonObject jobj;
		jobj.insert("user_id", line.at(0));
		jobj.insert("username", line.at(1));
		jobj.insert("gender", line.at(2) == "男" ? 1 : (line.at(2) == "女" ? 2 : 0));
		jobj.insert("telephone", line.at(3));
		jobj.insert("password", "123456");
		jarr.append(jobj);
	}
	SHttpClient(URL("/api/user/batch_create")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.json({ {"lists", jarr} })
		.success([=](const QByteArray& data)
			{
				QJsonParseError error;
				auto jdom = QJsonDocument::fromJson(data, &error);
				if (error.error != QJsonParseError::NoError)
				{
					qDebug() << "Parse json error:" << error.errorString();
					return;
				}
				onSearch();
			}).post();
}

void UserManagePage::readExcelFile(const QString& fileName)
{
	using namespace QXlsx;
	Document doc(fileName);
	if (!doc.load())
	{
		qDebug() << fileName << ": load file failed!";
		return;
	}
	//获取工作簿
	//Workbook* book = doc.workbook();
	//获取工作表
	Worksheet* sheet = doc.currentWorksheet();
	//获取单元格范围
	CellRange range = sheet->dimension();

	QJsonArray jarr;
	for (int row = 2; row <= range.rowCount(); ++row)
	{
		QJsonObject jobj;
		for (int col = 1; col <= range.columnCount(); ++col)
		{
			Cell* cell = sheet->cellAt(row, col);
			if (cell)
			{
				auto value = cell->value().toString();
				//qDebug() << cell->value().toString();
				if (col == 1)
				{
					jobj.insert("user_id", value);
				}
				else if (col == 2)
				{
					jobj.insert("username", value);
				}
				else if (col == 3)
				{
					jobj.insert("gender", value == "男" ? 1 : (value == "女" ? 2 : 0));
				}
				else if (col == 4)
				{
					jobj.insert("telephone", value);
				}
			}
		}
		jarr.append(jobj);
	}
	SHttpClient(URL("/api/user/batch_create")).debug(true)
		.header("Authorization", "Bearer" + sApp->getUserData("user/token").toString())
		.json({ {"lists", jarr} })
		.success([=](const QByteArray& data)
			{
				QJsonParseError error;
				auto jdom = QJsonDocument::fromJson(data, &error);
				if (error.error != QJsonParseError::NoError)
				{
					qDebug() << "Parse json error:" << error.errorString();
					return;
				}
				onSearch();
			}).post();
}

void UserManagePage::writeCSVFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		qDebug() << fileName << ": open file error:" << file.errorString();
		return;
	}
	QTextStream stream(&file);
	//写表头
	for (int c = 0; c < m_model->columnCount(); c++)
	{
		stream << m_model->horizontalHeaderItem(c)->text();
		if (c < m_model->columnCount() - 1)
		{
			stream << ",";
		}
	}
	stream << "\n";
	//写数据
	for (int r = 0; r < m_model->rowCount(); r++)
	{
		for (int c = 0; c < m_model->columnCount(); c++)
		{
			auto item = m_model->item(r, c);
			if (item)
			{
				stream << item->text();
				if (c < m_model->columnCount() - 1)
				{
					stream << ",";
				}
			}

		}
		stream << "\n";
	}

}

void UserManagePage::writeExcelFile(const QString& fileName)
{
}
