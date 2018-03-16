#include "dialog_selector_employee.h"
#include "cs_networker.h"
#include "cs_command.h"

DialogSelectorEmployee::DialogSelectorEmployee(QString title, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	m_width = width; m_height = height;
	setModal(true);

	btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");
	btnConfirm->setEnabled(false);
	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");
	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	
	QLabel* m_lbMessage = new QLabel("직원을 선택하세요.");
	m_lbMessage->setFixedSize(m_width - 150, 25);
	//m_lbMessage->setContentsMargins(5, 0, 0, 0);
	m_lbMessage->setAlignment(Qt::AlignCenter);
	m_wdTail->layout()->addWidget(m_lbMessage);
	
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);
	
    NetWorker* n = NetWorker::instance();
	n->getUserList()->request();

	m_zoneEmployees = new QWidget(this);
	m_zoneEmployees->setLayout(new QVBoxLayout(m_zoneEmployees));
	m_zoneEmployees->setFixedSize(m_width, m_height);
	m_zoneEmployees->layout()->setAlignment(Qt::AlignTop);
	m_zoneEmployees->layout()->setMargin(0);
	m_zoneEmployees->layout()->setSpacing(0);

	m_zoneEmployees->layout()->addWidget(m_wdTail);

	refresh();

	connect(m, SIGNAL(employeesChanged()), this, SLOT(refresh()));

}
void DialogSelectorEmployee::setParent(WidgetDialog* parent)
{
	m_parent = parent;
}
void DialogSelectorEmployee::activate()
{
	btnConfirm->setEnabled(true);
}

void DialogSelectorEmployee::refresh()
{
	int cnt = m->countEmployee();
	if (cnt <= 0) return;

	if (m_table != nullptr)
		m_zoneEmployees->layout()->removeWidget(m_table);

	int columnCount = 3;
	QStringList tableHeader;
	tableHeader << "번호" << "이름" << "관리자";
	m_table = new QTableWidget(cnt, columnCount, this);
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_table->setSelectionMode(QAbstractItemView::SingleSelection);
	m_table->setFixedSize(m_width, m_height);
	m_table->horizontalScrollBar()->setDisabled(true);
	m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	updateTable();
	m_table->setHorizontalHeaderLabels(tableHeader);
	m_table->verticalHeader()->hide();

	for (int row = 0; row < cnt; row++)
	{
		Employee* dv = m->employees().at(row);

		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(row + 1));
		item0->setTextAlignment(Qt::AlignCenter);
		m_table->setItem(row, 0, item0);

		QTableWidgetItem* item1 = new QTableWidgetItem(dv->nameUser());
		item1->setTextAlignment(Qt::AlignCenter);
		m_table->setItem(row, 1, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->manager() ? "O" : "X");
		item2->setTextAlignment(Qt::AlignCenter);
		m_table->setItem(row, 2, item2);
	}
	m_zoneEmployees->layout()->addWidget(m_table);
	update();

	connect(m_table, SIGNAL(itemSelectionChanged()), this, SLOT(activate()));
	//connect(m_table, SIGNAL(itemDoubleClicked()), this, SLOT(confirm()));
}

void DialogSelectorEmployee::updateTable()
{
	m_table->setFixedSize(m_width, m_height);
	m_table->setColumnWidth(0, m_table->width() * 0.10);
	m_table->setColumnWidth(1, m_table->width() * 0.70);
	m_table->setColumnWidth(2, m_table->width() * 0.20 -10);
	m_table->setStyleSheet("border: 0px;");
}
void DialogSelectorEmployee::confirm()
{
	m_parent->notify(m_table->currentRow());
	close();
}
void DialogSelectorEmployee::cancel()
{
	close();
}
