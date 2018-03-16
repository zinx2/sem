#include "dialog_alarm.h"
#include "cs_command.h"
#include "cs_model.h"
DialogAlarm::DialogAlarm(QString title, QString message, int width, int height, QWidget *parent)
	: WidgetDialog(title,width,height,parent)
{
	setModal(true);
	Command* btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");

	m_zoneMessage = new QWidget(this);
	m_zoneMessage->setLayout(new QVBoxLayout(m_zoneMessage));
	m_zoneMessage->layout()->setAlignment(Qt::AlignTop);
	m_zoneMessage->setFixedSize(width-10, height - m_wdTail->height());
	m_wdContents->layout()->addWidget(m_zoneMessage);

	QLabel* lbMessage = new QLabel(m_zoneMessage);
	lbMessage->setText(message);
	lbMessage->setWordWrap(true);
	lbMessage->setFixedSize(width, m_zoneMessage->height());
	lbMessage->setAlignment(Qt::AlignTop);
	m_wdContents->layout()->addWidget(m_zoneMessage);
	m_wdContents->layout()->setContentsMargins(5, 5, 0, 5);

	m_wdTail->layout()->addWidget(btnConfirm);
	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(this, SIGNAL(rejected()), this, SLOT(confirm()));
}

void DialogAlarm::confirm()
{
	m->setModal(false);
	close();
	emit yes();
}