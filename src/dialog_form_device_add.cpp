#include "dialog_form_device_add.h"
#include "dialog_alarm.h"
#include "dialog_question.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_networker.h"
#include "dialog_selector_employee.h"
DialogFormDeviceAdd::DialogFormDeviceAdd(QString title, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	m_net = NetWorker::instance();
	connect(m_net, SIGNAL(update(bool isSuccess)), this, SLOT(alarm(bool isSuccess)));
	connect(m_net, SIGNAL(upload(bool isSuccess)), this, SLOT(sign(bool isSuccess)));
	setModal(true);
	btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");
	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");
	Command* btnSaerch = new Command("search", "부서찾기", 70, 30);
	btnSaerch->setStyleSheet("background: #e1e1e1;");
	Command* btnInit = new Command("init", "초기화", 70, 30);
	btnInit->setStyleSheet("background: #e1e1e1;");

	m_lbMessage = new QLabel("장비명을 입력해주세요.");
	m_lbMessage->setFixedSize(width, 25);
	m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	m_wdTail->layout()->addWidget(m_lbMessage);

	m_wdTail->layout()->addWidget(btnInit);
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);

	m_zoneDevice = new QWidget(this);
	m_zoneDevice->setLayout(new QHBoxLayout(m_zoneDevice));
	m_zoneDevice->setFixedSize(width, 35);
	m_zoneDevice->layout()->setAlignment(Qt::AlignVCenter);
	m_zoneDevice->layout()->setMargin(0);
	m_zoneDevice->layout()->setSpacing(5);
	m_zoneDevice->layout()->setContentsMargins(10, 5, 0, 0);
	QLabel* lbDevice = new QLabel("장비명");
	lbDevice->setFixedSize(50, 25);
	lbDevice->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edNameDevice = new QTextEdit(this);
	m_edNameDevice->setFixedSize(200, 25);
	m_edNameDevice->setAlignment(Qt::AlignHCenter);
	m_edNameDevice->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edNameDevice->setStyleSheet("background:white;");
	m_zoneDevice->layout()->addWidget(lbDevice);
	m_zoneDevice->layout()->addWidget(m_edNameDevice);
	m_wdContents->layout()->addWidget(m_zoneDevice);

	m_zoneNoAsset = new QWidget(this);
	m_zoneNoAsset->setLayout(new QHBoxLayout(m_zoneNoAsset));
	m_zoneNoAsset->setFixedSize(width, 35);
	m_zoneNoAsset->layout()->setAlignment(Qt::AlignVCenter);
	m_zoneNoAsset->layout()->setMargin(0);
	m_zoneNoAsset->layout()->setSpacing(5);
	m_zoneNoAsset->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbNoAsset = new QLabel("자산번호");
	lbNoAsset->setFixedSize(50, 25);
	lbNoAsset->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edNoAsset = new QTextEdit(this);
	m_edNoAsset->setFixedSize(200, 25);
	m_edNoAsset->setAlignment(Qt::AlignHCenter);
	m_edNoAsset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edNoAsset->setStyleSheet("background:white;");
	m_zoneNoAsset->layout()->addWidget(lbNoAsset);
	m_zoneNoAsset->layout()->addWidget(m_edNoAsset);
	m_wdContents->layout()->addWidget(m_zoneNoAsset);

	m_zonePart = new QWidget(this);
	m_zonePart->setLayout(new QHBoxLayout(m_zonePart));
	m_zonePart->setFixedSize(width, 35);
	m_zonePart->layout()->setAlignment(Qt::AlignVCenter);
	m_zonePart->layout()->setMargin(0);
	m_zonePart->layout()->setSpacing(5);
	m_zonePart->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbPart = new QLabel("소속파트");
	lbPart->setFixedSize(50, 25);
	lbPart->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edPart = new QTextEdit(this);
	m_edPart->setFixedSize(200, 25);
	m_edPart->setAlignment(Qt::AlignHCenter);
	m_edPart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edPart->setStyleSheet("background:white;");
	m_zonePart->layout()->addWidget(lbPart);
	m_zonePart->layout()->addWidget(m_edPart);
	m_zonePart->layout()->addWidget(btnSaerch);
	m_wdContents->layout()->addWidget(m_zonePart);

	m_zonePrice = new QWidget(this);
	m_zonePrice->setLayout(new QHBoxLayout(m_zonePrice));
	m_zonePrice->setFixedSize(width, 35);
	m_zonePrice->layout()->setAlignment(Qt::AlignVCenter);
	m_zonePrice->layout()->setMargin(0);
	m_zonePrice->layout()->setSpacing(5);
	m_zonePrice->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbPrice = new QLabel("취득금액");
	lbPrice->setFixedSize(50, 25);
	lbPrice->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edPrice = new QTextEdit(this);
	m_edPrice->setFixedSize(200, 25);
	m_edPrice->setAlignment(Qt::AlignHCenter);
	m_edPrice->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edPrice->setStyleSheet("background:white;");
	m_zonePrice->layout()->addWidget(lbPrice);
	m_zonePrice->layout()->addWidget(m_edPrice);
	m_wdContents->layout()->addWidget(m_zonePrice);

	m_zoneDate = new QWidget(this);
	m_zoneDate->setLayout(new QHBoxLayout(m_zoneDate));
	m_zoneDate->setFixedSize(width, 35);
	m_zoneDate->layout()->setAlignment(Qt::AlignVCenter);
	m_zoneDate->layout()->setMargin(0);
	m_zoneDate->layout()->setSpacing(5);
	m_zoneDate->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbDate = new QLabel("취득일자");
	lbDate->setFixedSize(50, 25);
	lbDate->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edDate = new QTextEdit(this);
	m_edDate->setFixedSize(200, 25);
	m_edDate->setAlignment(Qt::AlignHCenter);
	m_edDate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edDate->setStyleSheet("background:white;");
	m_zoneDate->layout()->addWidget(lbDate);
	m_zoneDate->layout()->addWidget(m_edDate);
	m_wdContents->layout()->addWidget(m_zoneDate);

	m_zoneUse = new QWidget(this);
	m_zoneUse->setLayout(new QHBoxLayout(m_zoneUse));
	m_zoneUse->setFixedSize(width, 95);
	m_zoneUse->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignTop);
	m_zoneUse->layout()->setMargin(0);
	m_zoneUse->layout()->setSpacing(0);
	m_zoneUse->layout()->setContentsMargins(10, 0, 10, 0);
	QLabel* lbUse = new QLabel("용도");
	lbUse->setFixedSize(50, 25);
	lbUse->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_edUse = new QTextEdit(this);
	m_edUse->setFixedSize(width-80, 50);
	m_edUse->setAlignment(Qt::AlignHCenter);
	m_edUse->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_edUse->setStyleSheet("background:white;");
	m_zoneUse->layout()->addWidget(lbUse);
	m_zoneUse->layout()->addWidget(m_edUse);
	m_wdContents->layout()->addWidget(m_zoneUse);

	//QLabel* lbNoAsset = new QLabel("자산번호");
	//lbNoAsset->setFixedSize(60, 30);
	//lbNoAsset->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	//edNoAsset = new QTextEdit("");
	//edNoAsset->setFixedSize(200, 25);
	//edNoAsset->setAlignment(Qt::AlignHCenter);
	//edNoAsset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//edNoAsset->setStyleSheet("background:white;");
	//m_zoneDevice->layout()->addWidget(lbNoAsset);
	//m_zoneDevice->layout()->addWidget(edNoAsset);


	//m_zonePart = new QWidget(this);
	//m_zonePart->setFixedSize(width, 55);
	//m_zoneNoAsset = new QWidget(this);
	//m_zoneNoAsset->setFixedSize(width, 55);
	//m_wdContents->layout()->addWidget(m_zonePart);
	//m_zonePrice = new QWidget(this);
	//m_zonePrice->setFixedSize(width, 55);
	//m_wdContents->layout()->addWidget(m_zonePrice);
	//m_zoneDate = new QWidget(this);
	//m_zoneDate->setFixedSize(width, 55);
	//m_wdContents->layout()->addWidget(m_zoneDate);
	//m_zoneUse = new QWidget(this);
	//m_zoneUse->setFixedSize(width, 55);
	//m_wdContents->layout()->addWidget(m_zoneUse);
	//m_zonePart = new QWidget(this);
	//m_zonePart->setLayout(new QHBoxLayout(m_zonePart));
	//m_zonePart->setFixedSize(width, 40);
	//m_zonePart->layout()->setAlignment(Qt::AlignVCenter);
	//m_zonePart->layout()->setMargin(0);
	//m_zonePart->layout()->setSpacing(5);
	//m_zonePart->layout()->setContentsMargins(10, 10, 0, 0);
	//QLabel* lbName = new QLabel("대출자");
	//lbName->setFixedSize(35, 30);
	//lbName->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	//m_zonePart->layout()->addWidget(lbName);
	//edPrice = new QTextEdit("");
	//edPrice->setFixedSize(130, 25);
	//edPrice->setAlignment(Qt::AlignHCenter);
	//edPrice->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//edPrice->setStyleSheet("background:white;");
	//m_zonePart->layout()->addWidget(edPrice);
	//m_zonePart->layout()->addWidget(btnSaerch);

	//QLabel* lbDate = new QLabel("대출일");
	//lbDate->setFixedSize(55, 30);
	//lbDate->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	//edDate = new QTextEdit("");
	//edDate->setFixedSize(150, 25);
	//edDate->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	//edDate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//edDate->setReadOnly(true);
	//edDate->setStyleSheet("background:white; padding-top:2px;");
	//m_zonePart->layout()->addWidget(lbDate);
	//m_zonePart->layout()->addWidget(edDate);
	//m_wdContents->layout()->addWidget(m_zonePart);

	//m_zoneUse = new QWidget(this);
	//m_zoneUse->setLayout(new QVBoxLayout(m_zoneUse));
	//m_zoneUse->setFixedSize(width, 110);
	//m_zoneUse->layout()->setAlignment(Qt::AlignTop);
	//m_zoneUse->layout()->setContentsMargins(10, 0, 0, 0);
	//QLabel* lbUse = new QLabel("용도");
	//lbUse->setFixedSize(70, 25);
	//lbUse->setAlignment(Qt::AlignBottom);
	//m_zoneUse->layout()->addWidget(lbUse);
	//edUse = new QTextEdit(m_zoneUse);
	//edUse->setFixedSize(width - 20, 75);
	//edUse->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//edUse->setStyleSheet("background: white;");
	//m_zoneUse->layout()->addWidget(edUse);
	////m_zoneUse->setStyleSheet("background:green");
	//m_wdContents->layout()->addWidget(m_zoneUse);

	//m_zonePrice = new QWidget(this);
	//m_zonePrice->setLayout(new QVBoxLayout(m_zonePrice));
	//m_zonePrice->setFixedSize(width, 30);
	//m_zonePrice->layout()->setAlignment(Qt::AlignTop);
	//m_zonePrice->layout()->setContentsMargins(10, 0, 0, 0);
	////m_zoneSecure->setStyleSheet("background:yellow");
	//cbSecure = new QCheckBox("보안점검(초기화)", this);
	//cbSecure->setFixedSize(width, m_zonePrice->height());
	//m_zonePrice->layout()->addWidget(cbSecure);
	//m_wdContents->layout()->addWidget(m_zonePrice);

	//m_zoneSign = new QWidget(this);
	//m_zoneSign->setLayout(new QVBoxLayout(m_zoneSign));
	////m_zoneSign->setStyleSheet("background:blue");
	//m_zoneSign->setFixedSize(width, 210);
	//m_zoneSign->layout()->setAlignment(Qt::AlignTop);
	//m_zoneSign->layout()->setContentsMargins(10, 0, 0, 0);
	//QLabel* lbSign = new QLabel("서명");
	//lbSign->setFixedSize(70, 25);
	//lbSign->setAlignment(Qt::AlignBottom);
	//m_zoneSign->layout()->addWidget(lbSign);
	//szSign = new DialogSignature(m_zoneSign);
	//szSign->setFixedSize(width - 20, 175);
	//m_zoneSign->layout()->addWidget(szSign);
	//m_wdContents->layout()->addWidget(m_zoneSign);

	//height = m_zoneDevice->height() + m_zoneNoAsset->height() + m_zonePart->height() 
	//		+ m_zonePrice->height() + m_zoneDate->height() + m_zoneUse->height();
	//m_wdContents->setFixedHeight(height);
	//setFixedHeight(height + 50);

	//connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	//connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	//connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	//connect(edNameDevice, SIGNAL(textChanged()), this, SLOT(activate()));
	//connect(edNoAsset, SIGNAL(textChanged()), this, SLOT(activate()));
	//connect(edPrice, SIGNAL(textChanged()), this, SLOT(activate()));
	//connect(edDate, SIGNAL(textChanged()), this, SLOT(activate()));
	//connect(cbSecure, SIGNAL(stateChanged(int)), this, SLOT(activate()));
	//connect(edUse, SIGNAL(textChanged()), this, SLOT(activate()));
	//connect(btnSaerch, SIGNAL(clicked()), this, SLOT(search()));
	//connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
}
void DialogFormDeviceAdd::search()
{
	DialogSelectorEmployee* selection = new DialogSelectorEmployee("직원 찾기", 400, 500, this);
	selection->setParent(this);
	selection->show();
}
void DialogFormDeviceAdd::activate()
{
	btnConfirm->setDisabled(m_edNameDevice->toPlainText().isEmpty() ||
		m_edNoAsset->toPlainText().isEmpty() ||
		m_edPrice->toPlainText().isEmpty() ||
		m_edDate->toPlainText().isEmpty() ||
		m_edUse->toPlainText().isEmpty());

	if (m_edPrice->toPlainText().isEmpty())
	{
		m_lbMessage->setText("대출자를 선택해주세요.");
	}
	else if (m_edUse->toPlainText().isEmpty())
	{
		m_lbMessage->setText("용도를 기입해주세요.");
	}
	else
	{
		m_lbMessage->setText("서명을 해주세요.");
	}
}
void DialogFormDeviceAdd::check(int state)
{
	if (state > 0) activate();
}
void DialogFormDeviceAdd::setData(QString noAsset)
{
	foreach(Device* d, m->devices())
	{
		if (!d->noAsset().compare(noAsset))
		{
			m_edNameDevice->setText(d->nameDevice());
			m_edNoAsset->setText(d->noAsset());
			QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
			m_edDate->setText(currentTime);
			break;
		}
	}
}
void DialogFormDeviceAdd::confirm()
{
	qDebug() << "confirm";
	if (!szSign->toImage())
	{
		m_alarm = new DialogAlarm("알림", "서명을 저장할 수 없습니다.", 300, 100);
		m_alarm->show();
	}

	QString strNameDevice = "장비명 : " + m_edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + m_edNoAsset->toPlainText() + "\n";
	QString strDate = "대출날짜 : " + m_edDate->toPlainText() + "\n";
	QString strNameUser = "대출자 : " + m_edPrice->toPlainText() + "\n";
	QString strUse = "용도 : " + m_edUse->toPlainText() + "\n";

	QString strSecureO = "보안점검 : O\n";
	QString strSecureX = "보안점검 : X\n";

	m_question = new DialogQuestion(
		"알림",
		"대출하시겠습니까?\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strDate
		+ strNameUser
		+ (cbSecure->isChecked() ? strSecureO : strSecureX)
		+ strUse, 300, 180);
	m_question->show();

	connect(m_question, SIGNAL(yes()), this, SLOT(allow()));
	connect(m_question, SIGNAL(no()), this, SLOT(none()));

}
void DialogFormDeviceAdd::cancel()
{
	qDebug() << "cancel";
	//m->setModal(false);
	close();
}
void DialogFormDeviceAdd::init()
{
	szSign->init();
}
void DialogFormDeviceAdd::allow()
{
	qDebug() << "allow";
	QString strNameDevice = "장비명 : " + m_edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + m_edNoAsset->toPlainText() + "\n";
	QString strDate = "대출날짜 : " + m_edDate->toPlainText() + "\n";
	QString strNameUser = "대출자 : " + m_edPrice->toPlainText() + "\n";
	QString strUse = "용도 : " + m_edUse->toPlainText() + "\n";

	QString strSecureO = "보안점검 : O\n";
	QString strSecureX = "보안점검 : X\n";


	m_net->borrowDevice(
		m_edNoAsset->toPlainText(),
		m_employee->noUser(),
		m_edUse->toPlainText())->request();


	m_alarm = new DialogAlarm(
		"알림",
		"대출이 완료되었습니다.\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strDate
		+ strNameUser
		+ (cbSecure->isChecked() ? strSecureO : strSecureX)
		+ strUse, 300, 180);

	disconnect(m_question, SIGNAL(yes()), this, SLOT(allow()));
	connect(m_alarm, SIGNAL(yes()), this, SLOT(finish()));
}

void DialogFormDeviceAdd::alarm(bool isSuccess)
{
	if (!isSuccess)
		error("대출을 할 수 없습니다.");
	m_alarm->show();
}
void DialogFormDeviceAdd::sign(bool isSuccess)
{
	if (!isSuccess)
		error("서명 파일 업로드에 실패하였습니다.");
	m_alarm->show();
}

void DialogFormDeviceAdd::error(QString message)
{
	m_alarm = new DialogAlarm("알림", message, 300, 100);
}


void DialogFormDeviceAdd::none()
{
	qDebug() << "none";
	m_question->hide();
}

void DialogFormDeviceAdd::finish()
{
	qDebug() << "finish";
	m_question->hide();
	m_alarm->hide();
	close();
}

void DialogFormDeviceAdd::notify(int row)
{
	m_employee = m->employees().at(row);
	m_edPrice->setText(m_employee->nameUser());
	update();
}