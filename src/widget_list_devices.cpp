#include "widget_list_devices.h"
#include "cs_networker.h"
#include "cs_qheader.h"
#include "dialog_form_device_add.h"
WidgetListDevices::WidgetListDevices(QWidget *parent) : WWidget(parent)
{
    NetWorker* n = NetWorker::instance();
	n->getDeviceList()->request();
	


	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);

	mainWidget = new QWidget(this);
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor02);
	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);

	this->layout()->addWidget(mainWidget);
	refresh();

	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));
	connect(m, SIGNAL(devicesChanged()), this, SLOT(refresh()));

}
void WidgetListDevices::updateTable()
{
	qDebug() << d->widthPage() << "/" << d->heightPage();
	table->setFixedSize(d->widthPage(), d->heightPage());
	table->setColumnWidth(0, table->width() * 0.05);
	table->setColumnWidth(1, table->width() * 0.15);
	table->setColumnWidth(2, table->width() * 0.15);
	table->setColumnWidth(3, table->width() * 0.15);
	table->setColumnWidth(4, table->width() * 0.13);
	table->setColumnWidth(5, table->width() * 0.07);
	table->setColumnWidth(6, table->width() * 0.30);
}
void WidgetListDevices::refresh()
{
	int cnt = m->countDevice();
	if (cnt <= 0) return;

	if (table != nullptr)
		mainWidget->layout()->removeWidget(table);

	int columnCount = 7;
	QStringList tableHeader;
	tableHeader << "번호" << "자산번호" << "장비명" << "취득금액" << "취득일자" << "대출여부" << "비교";
	table = new QTableWidget(m->countDevice(), columnCount, this);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setStyleSheet("border: 0px;");
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setFixedSize(d->widthPage(), d->heightPage());
	table->horizontalScrollBar()->setDisabled(true);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	updateTable();
	table->setHorizontalHeaderLabels(tableHeader);
	table->verticalHeader()->hide();

	for (int row = 0; row < cnt; row++)
	{
		Device* dv = m->devices().at(row);

		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(row+1));
		item0->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 0, item0);

		QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(dv->noAsset()));
		item1->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 1, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->nameDevice());
		item2->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 2, item2);

		QTableWidgetItem* item3 = new QTableWidgetItem(QString("%L1원  ").arg(dv->price()));
		item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		table->setItem(row, 3, item3);

		QTableWidgetItem* item4 = new QTableWidgetItem(dv->dateTaked());
		item4->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 4, item4);

		QTableWidgetItem* item5 = new QTableWidgetItem(dv->borrowed() ? "O" : "X");
		item5->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 5, item5);

		QTableWidgetItem* item6 = new QTableWidgetItem(dv->nameDevice());
		item6->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 6, item6);
	}	
	mainWidget->layout()->addWidget(table);
	update();
}
void WidgetListDevices::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	if (table != nullptr) updateTable();
}

void WidgetListDevices::deviceAdd()
{
	DialogFormDeviceAdd* form = new DialogFormDeviceAdd("장비추가", 500, 300, this);
	form->show();
}
void WidgetListDevices::deviceRemove()
{

}
void WidgetListDevices::deviceEdit()
{

}