#include "widget_list_devices.h"
#include "cs_networker.h"
#include "cs_qheader.h"
#include "dialog_form_device_add.h"
#include "dialog_form_device_edit.h"
#include "dialog_question.h"
#include "cs_component.h"
#include "cs_command.h"
WidgetListDevices::WidgetListDevices(QWidget *parent) : WWidget(parent)
{
	m_net = NetWorker::instance();
	m_net->getDeviceList()->request();

	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);
	this->layout()->setSpacing(0);

	m_cmdPrev = (new Command("cancel", "이전", 70, 30))->initStyleSheet("background: #e1e1e1;");
	connect(m_cmdPrev, SIGNAL(clicked()), this, SLOT(prev()));
	m_cmdNext = (new Command("search", "다음", 70, 30))->initStyleSheet("background: #e1e1e1;");
	connect(m_cmdNext, SIGNAL(clicked()), this, SLOT(next()));

	m_lbCnt = (new CPLabel(120, 40, getCountDevice()));

	mainWidget = new QWidget(this);
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor02);
	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setAlignment(Qt::AlignTop);
	mainWidget->layout()->setMargin(0);;
	mainWidget->layout()->setSpacing(0);

	this->layout()->addWidget(mainWidget);
	m_wdNavi = (new CPWidget(d->widthPage(), 40, new QHBoxLayout))
		->initAlignment(Qt::AlignRight)->initContentsMargins(0, 5, 0, 0)
		->append(m_lbCnt)
		->append(m_cmdPrev)
		->append(m_cmdNext);

	refresh();

	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));
	connect(m, SIGNAL(devicesChanged()), this, SLOT(refresh()));
}

void WidgetListDevices::updateTable()
{
	qDebug() << d->widthPage() << "/" << d->heightPage();
	table->setFixedSize(d->widthPage(), d->heightPage() - 80);
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
	tableHeader << "번호" << "자산번호" << "장비명" << "취득금액" << "취득일자" << "대출여부" << "비고";
	table = new QTableWidget(m->countDevice(), columnCount, this);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setStyleSheet("border: 0px;");
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setFixedSize(d->widthPage(), d->heightPage() - 80);
	table->horizontalScrollBar()->setDisabled(true);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	updateTable();
	table->setHorizontalHeaderLabels(tableHeader);
	table->verticalHeader()->hide();

	for (int row = 0; row < cnt; row++)
	{
		Device* dv = m->devices().at(row);

		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg((row+1) + (m->pageNumber()-1)*COUNT_PAGE));
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

		QTableWidgetItem* item6 = new QTableWidgetItem(dv->memo());
		item6->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 6, item6);
	}	
	mainWidget->layout()->addWidget(table);
	mainWidget->layout()->addWidget(m_wdNavi);
	m_lbCnt->setText(getCountDevice());
	m_cmdPrev->setEnabled(m->countCurrentDevice() > 20);
	m_cmdNext->setEnabled(m->countCurrentDevice() < m->countTotalDevice());
	update();
}
void WidgetListDevices::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	if (table != nullptr) updateTable();
	m_wdNavi->setFixedWidth(d->widthPage());
}

void WidgetListDevices::openDialogToAdd()
{
	DialogFormDeviceAdd* form = new DialogFormDeviceAdd("장비추가", 400, 300, this);
	form->show();
}
void WidgetListDevices::openDialogToRemove()
{
	if (table->currentRow() < 0) return;
	if (!table->item(table->currentRow(), 0)->isSelected()) return;
	qDebug() << m->devices().at(table->currentRow())->noDevice();
	qDebug() << table->item(table->currentRow(), 0)->isSelected();
	for (int i = 0; i < table->columnCount(); i++)
		table->item(table->currentRow(), i)->setSelected(false);
	
	QString strNameDevice = "장비명 : " + m->devices().at(table->currentRow())->nameDevice() + "\n";
	QString strNoAsset = "자산번호 : " + m->devices().at(table->currentRow())->noAsset() + "\n";

	m_question = new DialogQuestion(
		"알림",
		"선택한 장비를 삭제하시겠습니까?\n\n"
		+ strNameDevice
		+ strNoAsset, 300, 150);
	m_question->show();
	connect(m_question, SIGNAL(yes()), this, SLOT(deviceRemove()));
	connect(m_question, SIGNAL(no()), this, SLOT(closeDialogToRemove()));
}
void WidgetListDevices::deviceRemove()
{
	m_net->removeDevice(m->devices().at(table->currentRow())->noDevice())->request();
	closeDialogToRemove();
}
void WidgetListDevices::closeDialogToRemove()
{
	m_question->hide();
	disconnect(m_question, SIGNAL(yes()), this, SLOT(deviceRemove()));
	disconnect(m_question, SIGNAL(no()), this, SLOT(closeDialogToRemove()));
}
void WidgetListDevices::openDialogToEdit()
{
	if (table->currentRow() < 0) return;
	if (!table->item(table->currentRow(), 0)->isSelected()) return;
	qDebug() << m->devices().at(table->currentRow())->noDevice();
	qDebug() << table->item(table->currentRow(), 0)->isSelected();
	for (int i = 0; i < table->columnCount(); i++)
		table->item(table->currentRow(), i)->setSelected(false);

	DialogFormDeviceEdit* form = new DialogFormDeviceEdit(table->currentRow(), "장비편집", 400, 300, this);
	form->show();
}

QString WidgetListDevices::getCountDevice()
{
	return "보유장비(대) : " + QString("%1").arg(m->countCurrentDevice()) + "/" + QString("%1").arg(m->countTotalDevice());
}

void WidgetListDevices::prev()
{
	m->setPageNumber(m->pageNumber() - 1);
	qDebug() << m->pageNumber();
	m->setNotificator(new Notificator(true, "", Notificator::DVIList, false));

}
void WidgetListDevices::next()
{
	m->setPageNumber(m->pageNumber() + 1);
	qDebug() << m->pageNumber();
	m->setNotificator(new Notificator(true, "", Notificator::DVIList, false));
}