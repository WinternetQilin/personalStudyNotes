#include "SMaskWidget.h"

#include<QResizeEvent>
#include<QKeyEvent>

SMaskWidget::SMaskWidget(QWidget* parent)
	: QWidget(parent, Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus)
{
	setStyleSheet("background-color: rgba(194, 195, 201, 180);");
	setAttribute(Qt::WA_StyledBackground);
}

SMaskWidget* SMaskWidget::instance()
{
	static SMaskWidget* ins;
	if (!ins)
		ins = new SMaskWidget;
	return ins;
}

void SMaskWidget::setMainWidget(QWidget* widget)
{
	if (!widget)
	{
		qWarning("SMaskWidget::setMainWidget: Invalid widget!");
		return;
	}
	if (m_mainWidget)
	{
		qWarning("SMaskWidget::setMainWidget: Main widget already set!Will be changed!");
	}
	m_mainWidget = widget;

	this->setParent(m_mainWidget);
	this->hide();
	//this->resize(m_mainWidget->size());
	m_mainWidget->installEventFilter(this);
}

void SMaskWidget::addDialog(QWidget* dialog)
{
	if (!dialog)
	{
		qWarning("SMaskWidget::addDialog: Invalid dialog!");
		return;
	}
	auto it = m_dialogs.find(dialog);
	if (it != m_dialogs.end())
	{
		qWarning("SMaskWidget::addDialog: Dialog already added!");
		return;
	}
	m_dialogs.insert(dialog);
	dialog->installEventFilter(this);
}

void SMaskWidget::popUp(QWidget* dialog)
{
	if (!dialog)
	{
		qWarning("SMaskWidget::popUp: Invalid dialog!");
		return;
	}
	addDialog(dialog);
	if (m_dialogs.contains(dialog))
	{
		m_currentDialog = dialog;
		this->show();
		dialog->show();
		dialog->setFocus();
	}
}


bool SMaskWidget::eventFilter(QObject* obj, QEvent* ev)
{
	//因为可能要设置给多个窗口，所以要先判断当前是不是m_mainWidget
	if (obj == m_mainWidget)
	{
		if (ev->type() == QEvent::Resize)
		{
			this->resize(m_mainWidget->size());
			//也可以这么设置
			//this->setGeometry(m_mainWidget->rect());
		}
		
	}
	//自己遮罩层本身的事件
	else if (obj == this)
	{
		if (ev->type() == QEvent::Resize)
		{
			onResize();
		}
	}
	//其他弹出窗的事件
	else
	{
		if (ev->type() == QEvent::Hide)
		{
			this->hide();
		}
		else if (ev->type() == QEvent::KeyRelease)
		{
			auto kev = static_cast<QKeyEvent*>(ev);	
			if (kev->key() == Qt::Key_Escape)
			{
				m_currentDialog->hide();
				this->hide();
			}
		}
	}
	return false;
}

void SMaskWidget::resizeEvent(QResizeEvent* event)
{
	onResize();
}

void SMaskWidget::onResize()
{
	if (m_currentDialog)
	{
		m_currentDialog->setFixedHeight(this->height());
	}
}
