#include "widget_list_employees.h"
#include "cs_networker.h"
#include "cs_qheader.h"

WidgetListEmployees::WidgetListEmployees(QWidget *parent) : WWidget(parent)
{
	m_commandProvider = new CommandProvider();
    NetWorker* n = NetWorker::instance();
	n->getUserList()->request();

	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);

	mainWidget = new QWidget(this);
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor02);
	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setAlignment(Qt::AlignTop);
	mainWidget->layout()->setMargin(0);

	this->layout()->addWidget(mainWidget);
	refresh();

	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));
	connect(m, SIGNAL(employeesChanged()), this, SLOT(refresh()));
}

void WidgetListEmployees::refresh()
{
	int cnt = m->countEmployee();
	if (cnt <= 0) return;

	if (table != nullptr)
		mainWidget->layout()->removeWidget(table);

	int columnCount = 4;
	QStringList tableHeader;
	tableHeader << "번호" << "이름" << "관리자" << "관리";
	table = new QTableWidget(cnt, columnCount, this);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setFixedSize(d->widthPage(), d->heightPage() - d->heightTitleBar());
	table->horizontalScrollBar()->setDisabled(true);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	updateTable();
	table->setHorizontalHeaderLabels(tableHeader);
	table->verticalHeader()->hide();
	table->setGeometry(this->geometry());

	for (int row = 0; row < cnt; row++)
	{
		Employee* dv = m->employees().at(row);

		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(row + 1));
		item0->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 0, item0);

		QTableWidgetItem* item1 = new QTableWidgetItem(dv->nameUser());
		item1->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 1, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->manager() ? "O" : "X");
		item2->setTextAlignment(Qt::AlignCenter);
		table->setItem(row, 2, item2);

		Command* cmdRemove = new Command(QString("%1").arg(dv->noUser()), "삭제", 50, 20);
		m_commandProvider->append(cmdRemove);
		cmdRemove->setStyleSheet("");
		connect(cmdRemove, &QPushButton::clicked, this, [=]()-> void {
			qDebug() << cmdRemove->tag();
			QList<Employee*> list = m->employees();
			//int index = 0;
			int noUser = -1;
			foreach(Employee* e, list)
			{	
				if (!QString("%1").arg(e->noUser()).compare(cmdRemove->tag()))
				{
					//list.removeAt(index);
					noUser = e->noUser();
					break;
				}
				//index++;
			}
			//m->setEmployees(list);
			NetWorker::instance()->expire(noUser)->request();
			//refresh();
		});

		QHBoxLayout *btnLayout = new QHBoxLayout();
		btnLayout->addWidget(cmdRemove);
		btnLayout->setMargin(0);
		QWidget *widgetBtns = new QWidget();
		widgetBtns->setLayout(btnLayout);
		table->setCellWidget(row, 3, widgetBtns);


	}
	mainWidget->layout()->addWidget(table);
	update();
}
void WidgetListEmployees::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
	if (table != nullptr) updateTable();
}
void WidgetListEmployees::updateTable()
{
	table->setFixedSize(d->widthPage(), d->heightPage() - d->heightTitleBar());
	table->setColumnWidth(0, table->width() * 0.05);
	table->setColumnWidth(1, table->width() * 0.35);
	table->setColumnWidth(2, table->width() * 0.20);
	table->setColumnWidth(3, table->width() * 0.40);
}
