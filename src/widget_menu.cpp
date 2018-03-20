#include "widget_menu.h"
#include "cs_command.h"

WidgetMenu::WidgetMenu(QWidget *parent) : WWidget(parent)
{
	m_commandProvider = new CommandProvider();
	btnWidth = parent->geometry().width();
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget1 = new QWidget;
	//mainWidget1->setGeometry(0, 0, parent->geometry().width(), parent->geometry().height() - 200);
	mainWidget1->setStyleSheet("background-color:" + d->c().testColor05);

	mainWidget2 = new QWidget;
	//mainWidget2->setGeometry(0, 0, 200, parent->geometry().height() - 200);
	mainWidget2->setStyleSheet("background-color:" + d->c().testColor05);

	mainHBox = new QVBoxLayout;
	mainHBox->addWidget(mainWidget1);
	mainHBox->addWidget(mainWidget2);
	mainHBox->layout()->setMargin(0);
	mainHBox->layout()->setSpacing(0);
    mainHBox->layout()->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainHBox);
	
	mainWidget1->setLayout(new QVBoxLayout);
	mainWidget1->layout()->setMargin(0);
	mainWidget1->layout()->setSpacing(0);
	mainWidget1->layout()->setAlignment(Qt::AlignTop);

	mainWidget2->setLayout(new QVBoxLayout);
	mainWidget2->layout()->setMargin(5);
	mainWidget2->layout()->setSpacing(5);
	mainWidget2->layout()->setAlignment(Qt::AlignBottom | Qt::AlignRight);

	m_commandProvider->append((new Command(DEVICE_LIST, "", btnWidth, 40))->initIcon(":/imgs/clipboard_18.png", qkor("장비목록")));
	mainWidget1->layout()->addWidget(m_commandProvider->command(DEVICE_LIST));

	m_commandProvider->append((new Command(DEVICE_MANAGE_LIST, "", btnWidth, 40))->initIcon(":/imgs/clipboard_18.png", qkor("관리대장")));
	mainWidget1->layout()->addWidget(m_commandProvider->command(DEVICE_MANAGE_LIST));

	m_commandProvider->append((new Command(EMPLOYEE_MANAGE_LIST, "", btnWidth, 40))->initIcon(":/imgs/clipboard_18.png", qkor("사원관리")));
	mainWidget1->layout()->addWidget(m_commandProvider->command(EMPLOYEE_MANAGE_LIST));
	
	////
	m_btnBorrow = new Command("borrow", "대출하기", btnWidth-10, 40);
	m_btnBorrow->initIcon(":/imgs/exit_18.png");
	m_btnBorrow->setStyleSheet("background: " + d->c().testColor07 + "; color:white;");
	mainWidget2->layout()->addWidget(m_btnBorrow);

	m_btnReturn = new Command("return", "반납하기", btnWidth-10, 40);
	m_btnReturn->initIcon(":/imgs/export_18.png");
	m_btnReturn->setStyleSheet("background: " + d->c().testColor07 + "; color:white;");
	mainWidget2->layout()->addWidget(m_btnReturn);

	m_commandProvider->select(DEVICE_LIST);
	connect(d, SIGNAL(widthMenuChanged()), this, SLOT(resize()));

	connect(m, SIGNAL(modalChanged()), this, SLOT(modal()));

	
}

void WidgetMenu::resize()
{
    qDebug() << "width: " << d->widthMenu();
	mainWidget1->setFixedWidth(d->widthMenu() - 200);
	mainWidget2->setGeometry(d->widthMenu() - 200, 0, 200, d->heightMenu());
}

void WidgetMenu::modal()
{
	setEnabled(!m->modal());
}