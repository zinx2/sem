#include "widget_dialog_signature.h"
#include "command.h"
#include "model.h"
WidgetDialogSignature::WidgetDialogSignature(QString title, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	Command* btnConfirm = new Command("confirm", "È®ÀÎ", width, 50);
	btnConfirm->setStyleSheet("color: white; background: #2b78e4;");
	m_wdTail->layout()->addWidget(btnConfirm);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
}

void WidgetDialogSignature::confirm()
{
	qDebug() << "confirm";
	m->setModal(false);
	close();
}