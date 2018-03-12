#include "qheader.h"
#include "command.h"
#include "model.h"
#include "sign_zone.h"
#include "networker.h"
DialogSign::DialogSign(QWidget *parent) : QDialog(parent)
{
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setFixedWidth(WIDTH_SIGN_ZONE + 20);
	setFixedHeight(HEIGHT_SIGN_ZONE + 100);

	setLayout(new QVBoxLayout(this));
	layout()->setSpacing(10);

	QLabel* lb = new QLabel(this);
	lb->setText("서명을 해주세요.");
	layout()->addWidget(lb);

	QWidget* zoneSign = new QWidget(this);
	zoneSign->setFixedWidth(WIDTH_SIGN_ZONE);
	zoneSign->setFixedHeight(HEIGHT_SIGN_ZONE);
	zoneSign->setStyleSheet("background: #f2f6f8; border: 0px solid black");
	zoneSign->setLayout(new QHBoxLayout);
	zoneSign->layout()->setMargin(0);
	signZone = new SignZone(this);
	zoneSign->layout()->addWidget(signZone);
	layout()->addWidget(zoneSign);

	QWidget* zoneBtn = new QWidget(this);
	zoneBtn->setLayout(new QHBoxLayout(this));
	layout()->addWidget(zoneBtn);
	
	Command* cmdConfirm = new Command("confirm", "확인", 235, 45);
	zoneBtn->layout()->addWidget(cmdConfirm);
	Command* cmdCancel = new Command("cancel", "취소", 235, 45);
	zoneBtn->layout()->addWidget(cmdCancel);
	zoneBtn->layout()->setAlignment(Qt::AlignCenter);
	zoneBtn->setContentsMargins(0, 0, 0, 0);
	zoneBtn->layout()->setMargin(0);

	connect(cmdCancel, SIGNAL(clicked()), this, SLOT(off()));
	connect(cmdConfirm, SIGNAL(clicked()), this, SLOT(save()));
	
	m = Model::instance();
}
void DialogSign::save()
{
	if (signZone->toImage())
	{
		NetWorker* n = NetWorker::getInstance();
		QString filePath = QDir::currentPath() + "/tmp.png";
		n->uploadFile(filePath)->request();
		off();
	}
	emit saved();
}
void DialogSign::off()
{
	close();
	m->setModal(false);
}