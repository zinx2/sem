#include "widget_list_managements.h"
#include "cs_networker.h"
#include "cs_qheader.h"
#include "cs_command.h"
#include "cs_component.h"
WidgetListManagements::WidgetListManagements(QWidget *parent) : WWidget(parent)
{
    NetWorker* n = NetWorker::instance();
	n->getRentList()->request();

	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);

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
	mainWidget->layout()->setMargin(0);
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
	connect(m, SIGNAL(rentsChanged()), this, SLOT(refresh()));
}

void WidgetListManagements::refresh()
{
	int cnt = m->countRent();
	if (cnt <= 0) return;

	if (table != nullptr)
		mainWidget->layout()->removeWidget(table);

	int columnCount = 10;
	QStringList tableHeader;
	tableHeader << "번호" << "자산번호" << "장비명" << "대출날짜" << "대출자" << "서명" << "반납날짜" << "확인자" << "서명" << "확인";
	table = new QTableWidget(cnt, columnCount, this);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setStyleSheet("border: 0px;");
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setFixedSize(d->widthPage(), d->heightPage() - 80);
	table->horizontalScrollBar()->setDisabled(true);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	updateTable();
	table->setHorizontalHeaderLabels(tableHeader);
	table->verticalHeader()->hide();
	table->setGeometry(this->geometry());

	for (int row = 0; row < cnt; row++)
	{
		Rent* dv = m->rents().at(row);

		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg((row + 1) + (m->pageNumber() - 1)*COUNT_PAGE));
		item0->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 0, item0);

		QTableWidgetItem* item1 = new QTableWidgetItem(dv->noAsset());
		item1->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 1, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->nameDevice());
		item2->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 2, item2);

		QTableWidgetItem* item3 = new QTableWidgetItem(dv->dateBorrowed());
		item3->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 3, item3);

		QTableWidgetItem* item4 = new QTableWidgetItem(dv->nameUser());
		item4->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 4, item4);

		QTableWidgetItem* item5 = new QTableWidgetItem(dv->signUser());
		item5->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 5, item5);

		QTableWidgetItem* item6 = new QTableWidgetItem(dv->dateReturned());
		item6->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 6, item6);

		QTableWidgetItem* item7 = new QTableWidgetItem(dv->nameAdmin());
		item7->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 7, item7);

		QTableWidgetItem* item8 = new QTableWidgetItem(dv->signAdmin());
		item8->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 8, item8);

		QTableWidgetItem* item9 = new QTableWidgetItem(dv->completed() ? "O" : "X");
		item9->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 9, item9);
	}
	mainWidget->layout()->addWidget(table);
	mainWidget->layout()->addWidget(m_wdNavi);
	m_lbCnt->setText(getCountDevice());
	m_cmdPrev->setEnabled(m->countCurrentDevice() > 20);
	m_cmdNext->setEnabled(m->countCurrentDevice() < m->countTotalDevice());
	update();
}
void WidgetListManagements::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	if (table != nullptr) updateTable();
	m_wdNavi->setFixedWidth(d->widthPage());
}
void WidgetListManagements::updateTable()
{
	table->setFixedSize(d->widthPage(), d->heightPage() - 80);
	table->setColumnWidth(0, table->width() * 0.05);
	table->setColumnWidth(1, table->width() * 0.10);
	table->setColumnWidth(2, table->width() * 0.10);
	table->setColumnWidth(3, table->width() * 0.15);
	table->setColumnWidth(4, table->width() * 0.10);
	table->setColumnWidth(5, table->width() * 0.10);
	table->setColumnWidth(6, table->width() * 0.15);
	table->setColumnWidth(7, table->width() * 0.10);
	table->setColumnWidth(8, table->width() * 0.10);
	table->setColumnWidth(9, table->width() * 0.05);
}

QString WidgetListManagements::getCountDevice()
{
	return "개수 : " + QString("%1").arg(m->countCurrentDevice()) + "/" + QString("%1").arg(m->countTotalDevice());
}

void WidgetListManagements::prev()
{
	m->setPageNumber(m->pageNumber() - 1);
	qDebug() << m->pageNumber();
	m->setNotificator(new Notificator(true, "", Notificator::MNGList, false));

}
void WidgetListManagements::next()
{
	m->setPageNumber(m->pageNumber() + 1);
	qDebug() << m->pageNumber();
	m->setNotificator(new Notificator(true, "", Notificator::MNGList, false));
}
