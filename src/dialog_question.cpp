#include "dialog_question.h"
#include "cs_command.h"
#include "cs_model.h"
DialogQuestion::DialogQuestion(QString title, QString message, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	setModal(true);
	Command* btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");

	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");

	m_zoneMessage = new QWidget(this);
	m_zoneMessage->setLayout(new QVBoxLayout(m_zoneMessage));
	m_zoneMessage->layout()->setAlignment(Qt::AlignTop);
	m_zoneMessage->setFixedSize(width - 10, height - m_wdTail->height());
	m_wdContents->layout()->addWidget(m_zoneMessage);

	QLabel* lbMessage = new QLabel(m_zoneMessage);
	lbMessage->setText(message);
	lbMessage->setWordWrap(true);
	lbMessage->setFixedSize(width, m_zoneMessage->height());
	lbMessage->setAlignment(Qt::AlignTop);
	m_wdContents->layout()->addWidget(m_zoneMessage);
	m_wdContents->layout()->setContentsMargins(5, 5, 0, 5);

	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);
	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	//connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
}

void DialogQuestion::cancel()
{
	emit no();
}
void DialogQuestion::reject()
{
	emit no();
}
void DialogQuestion::confirm()
{
	emit yes();
}