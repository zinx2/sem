#include "widget_page.h"
#include "cs_networker.h"
#include "widget_list_devices.h"
#include "widget_list_employees.h"
#include "widget_list_managements.h"
#include "cs_command.h"

WidgetPage::WidgetPage(QWidget *parent) : WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor05);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);

	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);
	mainWidget->layout()->setSpacing(0);
	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));

	m_wdCmds = new QWidget(this);
	mainWidget->layout()->addWidget(m_wdCmds);
	m_wdCmds->setLayout(new QHBoxLayout);
	m_wdCmds->setFixedHeight(40);
	m_wdCmds->layout()->setSpacing(5);
	m_wdCmds->layout()->setMargin(0);
	m_wdCmds->layout()->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

	pgWidget = new QWidget(this);
	pgWidget->setLayout(new QVBoxLayout);
	pgWidget->layout()->setSpacing(0);
	pgWidget->layout()->setContentsMargins(0, 0, 0, 0);
	mainWidget->layout()->addWidget(pgWidget);
	change(BTN_DEVICE_LIST);

	connect(m, SIGNAL(modalChanged()), this, SLOT(modal()));
}
void WidgetPage::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());

	pgWidget->setFixedWidth(d->widthPage());
	pgWidget->setFixedHeight(d->heightPage());

	m_wdCmds->setFixedWidth(d->widthPage());
	m_wdCmds->setFixedHeight(40);

	m_lbTitle->setFixedWidth(d->widthPage()-180);
}
void WidgetPage::change(QString tag)
{
	if (tag.isEmpty()) return;

	clearItem();
	clearCommand();
	if (!tag.compare(BTN_DEVICE_LIST))
	{
		m_wdCmds->layout()->addWidget(title("장비목록", m_wdCmds->width() - 180));
		m_wdCmds->layout()->setContentsMargins(5, 0, 5, 0);
		m_wdList = new WidgetListDevices(pgWidget);
		Command* cmdDVIAdd = new Command("dvi_add", "추가", 60, 30);
		cmdDVIAdd->setStyleSheet("background: #e1e1e1");
		m_wdCmds->layout()->addWidget(cmdDVIAdd);
		connect(cmdDVIAdd, SIGNAL(clicked()), m_wdList, SLOT(deviceAdd()));
		Command* cmdDVIRemove = new Command("dvi_remove", "삭제", 60, 30);
		cmdDVIRemove->setStyleSheet("background: #e1e1e1");
		m_wdCmds->layout()->addWidget(cmdDVIRemove);
		connect(cmdDVIRemove, SIGNAL(clicked()), m_wdList, SLOT(deviceRemove()));
		Command* cmdDVIEdit = new Command("dvi_edit", "편집", 60, 30);
		cmdDVIEdit->setStyleSheet("background: #e1e1e1");
		m_wdCmds->layout()->addWidget(cmdDVIEdit);
		connect(cmdDVIEdit, SIGNAL(clicked()), m_wdList, SLOT(deviceEdit()));
	}
	else if (!tag.compare(BTN_DEVICE_MANAGE_LIST))
	{
		m_wdList = new WidgetListManagements(pgWidget);
		m_wdCmds->layout()->addWidget(title("관리대장", m_wdCmds->width()));
		m_wdCmds->layout()->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	}
	else if (!tag.compare(BTN_EMPLOYEE_MANAGE_LIST))
	{
		m_wdList = new WidgetListEmployees(pgWidget);
		m_wdCmds->layout()->addWidget(title("직원목록", m_wdCmds->width()));
		m_wdCmds->layout()->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	}

	if(pgWidget != nullptr)
		pgWidget->layout()->addWidget(m_wdList);
}
QLabel* WidgetPage::title(QString txt, int width)
{
	m_lbTitle = new QLabel(txt);
	QFont font = this->font();
	font.setPointSize(13);
	m_lbTitle->setFont(font);
	m_lbTitle->setFixedSize(width, 40);
	m_lbTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_lbTitle->setStyleSheet("color:white;");
	return m_lbTitle;
}
void WidgetPage::clearCommand()
{
	int cnt = m_wdCmds->layout()->count();
	for (int i = 0; i < cnt; i++)
	{
		QLayoutItem* it = m_wdCmds->layout()->itemAt(0);
		Command* c = ((Command *)(it->widget()));
		m_wdCmds->layout()->removeWidget(c);
		m_wdCmds->layout()->removeItem(it);
		delete c;
	}
}
void WidgetPage::clearItem()
{
	int cnt = pgWidget->layout()->count();
	for (int i = 0; i < cnt; i++)
	{
		QLayoutItem* it = pgWidget->layout()->itemAt(0);
		WWidget* w = ((WWidget *)(it->widget()));
		pgWidget->layout()->removeWidget(w);
		delete w;
		pgWidget->layout()->removeItem(it);
	}
}

void WidgetPage::modal()
{
	setEnabled(!m->modal());
}