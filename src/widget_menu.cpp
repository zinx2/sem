#include "widget_menu.h"

WidgetMenu::WidgetMenu(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget1 = new QWidget;
	mainWidget1->setGeometry(0, 0, parent->geometry().width() - 200, parent->geometry().height());
	mainWidget1->setStyleSheet("background-color:" + d->c().blue01);

	mainWidget2 = new QWidget;
	mainWidget2->setGeometry(0, 0, 200, parent->geometry().height());
	mainWidget2->setStyleSheet("background-color:" + d->c().grary01);

	mainHBox = new QHBoxLayout;
	mainHBox->addWidget(mainWidget1);
	mainHBox->addWidget(mainWidget2);
	mainHBox->layout()->setMargin(0);
	mainHBox->layout()->setSpacing(0);
    mainHBox->layout()->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainHBox);

	mainWidget1->setLayout(new QHBoxLayout);
	mainWidget1->layout()->setMargin(0);
	mainWidget1->layout()->setAlignment(Qt::AlignLeft);

	mainWidget2->setLayout(new QHBoxLayout);
	mainWidget2->layout()->setMargin(0);
	mainWidget2->layout()->setAlignment(Qt::AlignRight);

	m_btnDeviceList = createButton("장비목록");
	mainWidget1->layout()->setContentsMargins(5, 0, 0, 0);
	mainWidget1->layout()->addWidget(m_btnDeviceList);

	m_btnDeviceManagementList = createButton("관리대장");
	mainWidget1->layout()->addWidget(m_btnDeviceManagementList);

	m_btnEmployeeManagementList = createButton("사원관리");
	mainWidget1->layout()->addWidget(m_btnEmployeeManagementList);

	m_btnBorrow = createButton("대출");
	mainWidget2->layout()->addWidget(m_btnBorrow);

	m_btnReturn = createButton("반납");
	mainWidget2->layout()->setContentsMargins(0, 0, 5, 0);
	mainWidget2->layout()->addWidget(m_btnReturn);

	connect(d, SIGNAL(widthMenuChanged()), this, SLOT(resize()));
}

QPushButton* WidgetMenu::createButton(QString name) {
	QPushButton* btn = new QPushButton(mainWidget1);
	btn->setFixedSize(80, 40);

	//QPixmap pixmap(iconPath);
	//QIcon icon(pixmap);
	//btn->setIcon(icon);
	//btn->setIconSize(pixmap.rect().size() / 2);

	QFont font = btn->font();
	font.setPointSize(10);
	btn->setFont(font);
	btn->setText(name);
	btn->setStyleSheet("color: white; background-color: " + d->c().blue01);


	return btn;
}

void WidgetMenu::resize()
{
	mainWidget1->setFixedWidth(d->widthMenu() - 200);
	mainWidget2->setGeometry(d->widthMenu() - 200, 0, 200, d->heightMenu());
}