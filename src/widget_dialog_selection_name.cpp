#include "widget_dialog_selection_name.h"
#include "command.h"
#include "model.h"
WidgetDialogSelectionName::WidgetDialogSelectionName(int type, QString title, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	Command* btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");
	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");
	Command* btnSaerch = new Command("search", "이름찾기", 70, 30);
	btnSaerch->setStyleSheet("background: #e1e1e1;");
	Command* btnInit = new Command("init", "초기화", 70, 30);
	btnInit->setStyleSheet("background: #e1e1e1;");

	m_zoneName = new QWidget(this);
	m_zoneName->setLayout(new QHBoxLayout(m_zoneName));
	m_zoneName->setFixedSize(width, 40);
	//m_zoneName->setStyleSheet("background:red");
	m_zoneName->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	m_zoneName->layout()->setMargin(0);
	m_zoneName->layout()->setSpacing(10);
	m_zoneName->layout()->setContentsMargins(10, 10, 0, 0);
	QLabel* lbName = new QLabel(type == 0 ? "대출자" : "확인자");
	lbName->setFixedSize(35, 30);
	lbName->setAlignment(Qt::AlignVCenter);
	m_zoneName->layout()->addWidget(lbName);
	edName = new QTextEdit("직원선택");
	edName->setFixedSize(150, 25);
	edName->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	edName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edName->setReadOnly(true);
	edName->setStyleSheet("padding-top:2px;");
	m_zoneName->layout()->addWidget(edName);
	m_zoneName->layout()->addWidget(btnSaerch);
	m_wdContents->layout()->addWidget(m_zoneName);

	m_zoneUse = new QWidget(this);
	m_zoneUse->setLayout(new QVBoxLayout(m_zoneUse));
	m_zoneUse->setFixedSize(width, 110);
	m_zoneUse->layout()->setAlignment(Qt::AlignTop);
	m_zoneUse->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbUse = new QLabel("용도");
	lbUse->setFixedSize(70, 25);
	lbUse->setAlignment(Qt::AlignBottom);
	m_zoneUse->layout()->addWidget(lbUse);
	edUse = new QTextEdit(m_zoneUse);
	edUse->setFixedSize(width - 20, 75);
	edUse->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edUse->setStyleSheet("background: white;");
	m_zoneUse->layout()->addWidget(edUse);
	//m_zoneUse->setStyleSheet("background:green");
	m_wdContents->layout()->addWidget(m_zoneUse);
	if (type == 1) m_zoneUse->setEnabled(false);

	m_zoneSecure = new QWidget(this);
	m_zoneSecure->setLayout(new QVBoxLayout(m_zoneSecure));
	m_zoneSecure->setFixedSize(width, 30);
	m_zoneSecure->layout()->setAlignment(Qt::AlignTop);
	m_zoneSecure->layout()->setContentsMargins(10, 0, 0, 0);
	//m_zoneSecure->setStyleSheet("background:yellow");
	cbSecure = new QCheckBox("보안점검(초기화)", this);
	cbSecure->setFixedSize(width, m_zoneSecure->height());
	m_zoneSecure->layout()->addWidget(cbSecure);
	m_wdContents->layout()->addWidget(m_zoneSecure);
	if (type == 1) m_zoneSecure->setEnabled(false);

	m_zoneSign = new QWidget(this);
	m_zoneSign->setLayout(new QVBoxLayout(m_zoneSign));
	//m_zoneSign->setStyleSheet("background:blue");
	m_zoneSign->setFixedSize(width, 210);
	m_zoneSign->layout()->setAlignment(Qt::AlignTop);
	m_zoneSign->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbSign = new QLabel("서명");
	lbSign->setFixedSize(70, 25);
	lbSign->setAlignment(Qt::AlignBottom);
	m_zoneSign->layout()->addWidget(lbSign);
	szSign = new SignZone(m_zoneSign);
	szSign->setFixedSize(width - 20, 175);
	m_zoneSign->layout()->addWidget(szSign);
	m_wdContents->layout()->addWidget(m_zoneSign);

	height = m_zoneName->height() + m_zoneUse->height() +
		m_zoneSecure->height() + m_zoneSign->height();
	m_wdContents->setFixedHeight(height);
	setFixedHeight(height + 50);
	m_wdTail->layout()->addWidget(btnInit);
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(this, SIGNAL(rejected()), this, SLOT(cancel()));


}

void WidgetDialogSelectionName::confirm()
{
	qDebug() << "confirm";
	//m->setModal(false);
	close();
}
void WidgetDialogSelectionName::cancel()
{
	qDebug() << "cancel";
	//m->setModal(false);
	close();
}
void WidgetDialogSelectionName::init()
{
	szSign->init();
}
