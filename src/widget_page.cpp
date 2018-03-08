#include "widget_page.h"
#include "networker.h"
#include "widget_list_devices.h"
#include "widget_list_employees.h"
#include "widget_list_managements.h"

WidgetPage::WidgetPage(QWidget *parent) : WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor03);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);

	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);
	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));

	/* TESST */
	QWidget* wdTest = new QWidget;
	mainWidget->layout()->addWidget(wdTest);
	QHBoxLayout* lyTest = new QHBoxLayout;
	wdTest->setLayout(lyTest);
	wdTest->setFixedHeight(50);
	wdTest->layout()->setSpacing(0);
	wdTest->layout()->setAlignment(Qt::AlignLeft|Qt::AlignTop);

	QPushButton* btn1 = new QPushButton(wdTest);
	btn1->setFixedSize(100, 40);
	btn1->setText("/sem/getUserList");
	wdTest->layout()->addWidget(btn1);
	mainWidget->layout()->addWidget(wdTest);

	QPushButton* btn2 = new QPushButton(wdTest);
	btn2->setFixedSize(100, 40);
	btn2->setText("/sem/getPartList");
	wdTest->layout()->addWidget(btn2);

	QPushButton* btn3 = new QPushButton(wdTest);
	btn3->setFixedSize(100, 40);
	btn3->setText("/sem/getDeviceList");
	wdTest->layout()->addWidget(btn3);

	QPushButton* btn4 = new QPushButton(wdTest);
	btn4->setFixedSize(100, 40);
	btn4->setText("/sem/getDeviceList");
	wdTest->layout()->addWidget(btn4);

	QPushButton* btn5 = new QPushButton(wdTest);
	btn5->setFixedSize(100, 40);
	btn5->setText("REFRESH LIST");
	wdTest->layout()->addWidget(btn5);

	textEdit = new QTextEdit(wdTest);
	connect(textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
	wdTest->layout()->addWidget(textEdit);

	connect(btn1, SIGNAL(clicked()), this, SLOT(test1()));
	connect(btn2, SIGNAL(clicked()), this, SLOT(test2()));
	connect(btn3, SIGNAL(clicked()), this, SLOT(test3()));
	connect(btn4, SIGNAL(clicked()), this, SLOT(test4()));
	connect(btn5, SIGNAL(clicked()), this, SLOT(test5()));

	pgWidget = new QWidget;
	pgWidget->setLayout(new QVBoxLayout);
	pgWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor03);
	pgWidget->layout()->setSpacing(0);
	pgWidget->layout()->setContentsMargins(0, 0, 0, 0);
	mainWidget->layout()->addWidget(pgWidget);
	listDVIces();
}
void WidgetPage::textChanged()
{
	QString barcode = textEdit->toPlainText();
	if(barcode.size() > 0 && barcode.at(barcode.size()-1) == '\n')
		qDebug() << textEdit->toPlainText();
}
void WidgetPage::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
}

void WidgetPage::test1()
{
	NetWorker* n = NetWorker::getInstance();
	n->getUserList();
}
void WidgetPage::test2()
{
	NetWorker* n = NetWorker::getInstance();
	n->getPartList();
}
void WidgetPage::test3()
{
	NetWorker* n = NetWorker::getInstance();
	n->getDeviceList();
}
void WidgetPage::test4()
{
	NetWorker* n = NetWorker::getInstance();
	n->getDeviceList(1, 1);
}
void WidgetPage::test5()
{
	NetWorker* n = NetWorker::getInstance();
	wdLDVIces->refresh();
}
void WidgetPage::listDVIces()
{
	qDebug() << "listDVIces";
	clearItem();
	wdLDVIces = new WidgetListDevices(pgWidget);
	pgWidget->layout()->addWidget(wdLDVIces);
}
void WidgetPage::listMNGements()
{
	qDebug() << "listMNGements";
	clearItem();
	wdLMNGements = new WidgetListManagements(pgWidget);
	pgWidget->layout()->addWidget(wdLMNGements);
}
void WidgetPage::listEMPloyees()
{
	qDebug() << "listEMPloyees";
	clearItem();
	wdLEMPloyees = new WidgetListEmployees(pgWidget);
	pgWidget->layout()->addWidget(wdLEMPloyees);
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