#include "SNavBar.h"

#include <qpushbutton.h>

SNavBar::SNavBar(QWidget* parent)
	: QWidget(parent)
{
	init();
}

void SNavBar::addNav(const QString& text, int id)
{
	addNav(QIcon(), text, id);
}

void SNavBar::addNav(const QIcon& icon, const QString& text, int id)
{
	if (id == -1)id = m_lastId++;

	auto btn = new QPushButton(icon, text);
	m_buttonGroup->addButton(btn, id);
	m_vlayout->insertWidget(m_vlayout->count() - 1, btn);
}

void SNavBar::setNavHeader(const QString& text)
{
	m_header->setText(text);
}

void SNavBar::init()
{
	m_buttonGroup = new QButtonGroup(this);
	m_header = new QLabel;
	m_vlayout = new QVBoxLayout(this);

	m_header->setAlignment(Qt::AlignCenter);

	m_vlayout->addWidget(m_header);
	m_vlayout->addStretch();

	connect(m_buttonGroup, &QButtonGroup::idClicked, this, &SNavBar::idClicked);
	connect(m_buttonGroup, &QButtonGroup::buttonClicked, this, &SNavBar::buttonClicked);
}
