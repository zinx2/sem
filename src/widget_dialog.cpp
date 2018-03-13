#include "widget_dialog.h"
#include "design.h"
#include "model.h"

WidgetDialog::WidgetDialog(QString title, int width, int height, QWidget *parent) : QDialog(parent)
{
	d = Design::instance();
	m = Model::instance();

	Qt::WindowFlags flags = windowFlags();
	Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	flags = flags & (~helpFlag);

	setWindowTitle(title);
	setWindowFlags(flags);
	setFixedWidth(width); setFixedHeight(height);
	setStyleSheet("background: #eeeeee;");
	setLayout(new QVBoxLayout(this));
	layout()->setAlignment(Qt::AlignTop);
	layout()->setSpacing(0);
	layout()->setMargin(0);

	//QWidget* wdTitle = new QWidget(this);
	//wdTitle->setFixedWidth(width); wdTitle->setFixedHeight(25);
	//wdTitle->setStyleSheet("background: #2b78e4;");
	//wdTitle->setLayout(new QVBoxLayout(this));
	//wdTitle->layout()->setAlignment(Qt::AlignCenter);
	//layout()->addWidget(wdTitle);
	//QLabel* lbTitle = new QLabel(title, this);
	//lbTitle->setStyleSheet("color:white");
	//wdTitle->layout()->addWidget(lbTitle);

	m_wdContents = new QWidget(this);
	m_wdContents->setLayout(new QVBoxLayout);
	m_wdContents->layout()->setSpacing(0);
	m_wdContents->layout()->setMargin(0);
	m_wdContents->layout()->setAlignment(Qt::AlignTop);
	layout()->addWidget(m_wdContents);
	m_wdContents->setFixedWidth(width); m_wdContents->setFixedHeight(height - 40);
	//m_wdContents->setStyleSheet("background: transparent; border:0px; ");

	m_wdTail = new QWidget(this);
	layout()->addWidget(m_wdTail);
	m_wdTail->setFixedSize(width, 50);
	m_wdTail->setLayout(new QHBoxLayout(this));
	m_wdTail->layout()->setMargin(0);
	m_wdTail->layout()->setSpacing(10);
	m_wdTail->layout()->setContentsMargins(0, 0, 10, 0);
	m_wdTail->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
}