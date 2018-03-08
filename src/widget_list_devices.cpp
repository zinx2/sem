#include "widget_list_devices.h"
#include "networker.h"
#include <QMutexLocker>
#include <QList>
#include <QHeaderView>
WidgetListDevices::WidgetListDevices(QWidget *parent) : WWidget(parent)
{
	NetWorker* n = NetWorker::getInstance();
	n->getDeviceList();
	//this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));

	refresh();

	mainWidget = new QWidget(this);
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor01);
	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);
	
	scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	this->layout()->addWidget(scrollArea);	
	mainWidget->layout()->addWidget(table);
	scrollArea->setWidget(mainWidget);

	//mainWidget->setFixedSize(parent->size());
	
	


	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));
	connect(m, SIGNAL(devicesChanged()), this, SLOT(refresh()));
}
void WidgetListDevices::updateTable()
{
	table->setFixedSize(d->widthPage(), d->heightPage());
	table->setColumnWidth(0, table->width() * 0.15);
	table->setColumnWidth(1, table->width() * 0.20);
	table->setColumnWidth(2, table->width() * 0.15);
	table->setColumnWidth(3, table->width() * 0.13);
	table->setColumnWidth(4, table->width() * 0.07);
	table->setColumnWidth(5, table->width() * 0.30);
}
void WidgetListDevices::refresh()
{


	//if (table != nullptr)
	//	scrollArea->layout
	//	mainWidget->layout()->removeWidget(table);
	int cnt = m->countDevice();
	if (cnt <= 0) return;

	QStringList tableHeader;
	tableHeader << "자산번호" << "장비명" << "취득금액" << "취득일자" << "대출여부" << "비교";
	table = new QTableWidget(m->countDevice(), 6);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	updateTable();
	table->setHorizontalHeaderLabels(tableHeader);
	table->verticalHeader()->hide();
	table->setGeometry(this->geometry());


	for (int row = 0; row < cnt; row++)
	{
		Device* dv = m->devices().at(row);
		QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(dv->assetNo()));
		item1->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 0, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->name());
		item2->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 1, item2);

		QTableWidgetItem* item3 = new QTableWidgetItem(dv->price());
		item3->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 2, item3);

		QTableWidgetItem* item4 = new QTableWidgetItem(dv->date());
		item4->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 3, item4);

		QTableWidgetItem* item5 = new QTableWidgetItem(dv->borrowed() ? "O" : "X");
		item5->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 4, item5);

		QTableWidgetItem* item6 = new QTableWidgetItem(dv->name());
		item6->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 5, item6);
	}	
	//mainWidget->layout()->addWidget(table);
	//scrollArea->setWidget(imageLabel);
	update();
}
void WidgetListDevices::resize()
{
	scrollArea->setFixedWidth(d->widthPage());
	scrollArea->setFixedHeight(d->heightPage());
	if (table != nullptr) updateTable();
}