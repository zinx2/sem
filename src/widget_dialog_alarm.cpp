#include "widget_dialog_alarm.h"
#include "command.h"
#include "model.h"
WidgetDialogAlarm::WidgetDialogAlarm(QString title, int width, int height, QWidget *parent) 
	: WidgetDialog(title,width,height,parent)
{
	Command* btnConfirm = new Command("confirm", "확인", width, 50);
	btnConfirm->setStyleSheet("color: white; background: #2b78e4;");
	m_wdTail->layout()->addWidget(btnConfirm);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
}

void WidgetDialogAlarm::confirm()
{
	qDebug() << "confirm";
	m->setModal(false);
	close();
}