#include "dialog_form_device_return.h"
#include "dialog_alarm.h"
#include "dialog_question.h"
#include "dialog_selector_employee.h"
#include "cs_command.h"
#include "cs_model.h"
DialogFormDeviceReturn::DialogFormDeviceReturn(QString title, int width, int height, QWidget *parent)
    : WidgetDialog(title, width, height, parent)
{
	setModal(true);
    btnConfirm = new Command("confirm", "확인", 70, 30);
    btnConfirm->setStyleSheet("background: #e1e1e1;");
    Command* btnCancel = new Command("cancel", "취소", 70, 30);
    btnCancel->setStyleSheet("background: #e1e1e1;");
    Command* btnSaerch = new Command("search", "직원찾기", 70, 30);
    btnSaerch->setStyleSheet("background: #e1e1e1;");
    Command* btnInit = new Command("init", "초기화", 70, 30);
    btnInit->setStyleSheet("background: #e1e1e1;");

	m_lbMessage = new QLabel("직원을 선택하세요.");
	m_lbMessage->setFixedSize(width - 250, 25);
	m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_wdTail->layout()->addWidget(m_lbMessage);

	m_wdTail->layout()->addWidget(btnInit);
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);

	m_zoneDevice = new QWidget(this);
	m_zoneDevice->setLayout(new QHBoxLayout(m_zoneDevice));
	m_zoneDevice->setFixedSize(width, 55);
	//m_zoneName->setStyleSheet("background:red");
	m_zoneDevice->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	m_zoneDevice->layout()->setMargin(0);
	m_zoneDevice->layout()->setSpacing(5);
	m_zoneDevice->layout()->setContentsMargins(10, 10, 0, 0);
	QLabel* lbDevice = new QLabel("장비명");
	lbDevice->setFixedSize(35, 25);
	lbDevice->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	edNameDevice = new QTextEdit(this);
	edNameDevice->setFixedSize(200, 25);
	edNameDevice->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	edNameDevice->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edNameDevice->setReadOnly(true);
	edNameDevice->setStyleSheet("background:white;");
	m_zoneDevice->layout()->addWidget(lbDevice);
	m_zoneDevice->layout()->addWidget(edNameDevice);
	QLabel* lbNoAsset = new QLabel("자산번호");
	lbNoAsset->setFixedSize(60, 30);
	lbNoAsset->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	edNoAsset = new QTextEdit("");
	edNoAsset->setFixedSize(150, 25);
	edNoAsset->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	edNoAsset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edNoAsset->setReadOnly(true);
	edNoAsset->setStyleSheet("background:white; padding-top:2px;");
	m_zoneDevice->layout()->addWidget(lbNoAsset);
	m_zoneDevice->layout()->addWidget(edNoAsset);
	m_wdContents->layout()->addWidget(m_zoneDevice);

    m_zoneName = new QWidget(this);
    m_zoneName->setLayout(new QHBoxLayout(m_zoneName));
    m_zoneName->setFixedSize(width, 40);
    //m_zoneName->setStyleSheet("background:red");
    m_zoneName->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_zoneName->layout()->setMargin(0);
    m_zoneName->layout()->setSpacing(5);
    m_zoneName->layout()->setContentsMargins(10, 10, 0, 0);
    QLabel* lbName = new QLabel("확인자");
    lbName->setFixedSize(35, 30);
    lbName->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_zoneName->layout()->addWidget(lbName);
    edNameUserOrAdmin = new QTextEdit("");
    edNameUserOrAdmin->setFixedSize(130, 25);
    edNameUserOrAdmin->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    edNameUserOrAdmin->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edNameUserOrAdmin->setReadOnly(true);
	edNameUserOrAdmin->setStyleSheet("background:white; padding-top:2px;");
    m_zoneName->layout()->addWidget(edNameUserOrAdmin);
    m_zoneName->layout()->addWidget(btnSaerch);
	QLabel* lbDate = new QLabel("반납일");
    lbDate->setFixedSize(55, 30);
	lbDate->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	edDateBorrowedOrReturned = new QTextEdit("");
	edDateBorrowedOrReturned->setFixedSize(150, 25);
	edDateBorrowedOrReturned->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	edDateBorrowedOrReturned->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edDateBorrowedOrReturned->setReadOnly(true);
	edDateBorrowedOrReturned->setStyleSheet("background:white; padding-top:2px;");
	m_zoneName->layout()->addWidget(lbDate);
	m_zoneName->layout()->addWidget(edDateBorrowedOrReturned);
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
    edUse->setFixedSize(width-20, 75);
    edUse->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edUse->setStyleSheet("background: white;");
    m_zoneUse->layout()->addWidget(edUse);
    //m_zoneUse->setStyleSheet("background:green");
    m_wdContents->layout()->addWidget(m_zoneUse);
    m_zoneUse->setEnabled(false);

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
    m_zoneSecure->setEnabled(false);

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
    szSign = new DialogSignature(m_zoneSign);
    szSign->setFixedSize(width-20, 175);
    m_zoneSign->layout()->addWidget(szSign);
    m_wdContents->layout()->addWidget(m_zoneSign);

    height = m_zoneName->height() + m_zoneUse->height() +
            m_zoneSecure->height() + m_zoneSign->height() + m_zoneDevice->height();
    m_wdContents->setFixedHeight(height);
    setFixedHeight(height + 50);

    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(edNameDevice, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edNoAsset, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edNameUserOrAdmin, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edDateBorrowedOrReturned, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(cbSecure, SIGNAL(stateChanged(int)), this, SLOT(activate()));
	connect(edUse, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(btnSaerch, SIGNAL(clicked()), this, SLOT(search()));
    connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
}
void DialogFormDeviceReturn::search()
{
	DialogSelectorEmployee* selection = new DialogSelectorEmployee("직원 찾기", 400, 500, this);
	selection->setParent(this);
	selection->show();
}
void DialogFormDeviceReturn::activate()
{
	btnConfirm->setDisabled(edNameDevice->toPlainText().isEmpty() ||
		edNoAsset->toPlainText().isEmpty() ||
		edNameUserOrAdmin->toPlainText().isEmpty() ||
		edDateBorrowedOrReturned->toPlainText().isEmpty() ||
		edUse->toPlainText().isEmpty());

	if (edNameUserOrAdmin->toPlainText().isEmpty())
	{
		QString human = m_type == 0 ? "대출자" : "반납자";
		m_lbMessage->setText(human + "를 선택해주세요.");
	}
	else if (edUse->toPlainText().isEmpty())
	{
		m_lbMessage->setText("용도를 기입해주세요.");
	}
	else
	{
		m_lbMessage->setText("서명을 해주세요.");
	}
}
void DialogFormDeviceReturn::check(int state)
{
	if(state>0) activate();
}
void DialogFormDeviceReturn::setData(QString noAsset)
{
	foreach(Device* d, m->devices())
	{
		if (!d->noAsset().compare(noAsset))
		{
			edNameDevice->setText(d->nameDevice());
			edNoAsset->setText(d->noAsset());
			QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
			edDateBorrowedOrReturned->setText(currentTime);
			break;
		}
	}	
}
void DialogFormDeviceReturn::confirm()
{
    qDebug() << "confirm";
	QString strNameDevice = "장비명 : " + edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + edNoAsset->toPlainText() + "\n";
	QString strDate = "대출날짜 : " + edDateBorrowedOrReturned->toPlainText() + "\n";
	QString strNameUser = "대출자 : " + edNameUserOrAdmin->toPlainText() + "\n";
	QString strUse = "용도 : " + edUse->toPlainText() + "\n";

	QString strSecureO = "보안점검 : O\n";
	QString strSecureX = "보안점검 : X\n";

	QString askType = m_type == 0 ? "대출" : "반납";
	m_question = new DialogQuestion(
		"알림",
		askType + "하시겠습니까?\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strDate
		+ strNameUser
		+ (cbSecure->isChecked() ? strSecureO : strSecureX)
		+ strUse, 300, 180);
	m_question->show();

	connect(m_question, SIGNAL(yes()), this, SLOT(renew()));
	connect(m_question, SIGNAL(no()), this, SLOT(none()));

}
void DialogFormDeviceReturn::cancel()
{
    qDebug() << "cancel";
    //m->setModal(false);
    close();
}
void DialogFormDeviceReturn::init()
{
	szSign->init();
}
void DialogFormDeviceReturn::renew()
{
	qDebug() << "renew";
	QString strNameDevice = "장비명 : " + edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + edNoAsset->toPlainText() + "\n";
	QString strDate = "대출날짜 : " + edDateBorrowedOrReturned->toPlainText() + "\n";
	QString strNameUser = "대출자 : " + edNameUserOrAdmin->toPlainText() + "\n";
	QString strUse = "용도 : " + edUse->toPlainText() + "\n";

	QString strSecureO = "보안점검 : O\n";
	QString strSecureX = "보안점검 : X\n";

	//borrow device
	//파일 업로드
	//사인 전송

	QString askType = m_type == 0 ? "대출" : "반납";
	m_alarm = new DialogAlarm(
		"알림",
		askType + "이 완료되었습니다.\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strDate
		+ strNameUser
		+ (cbSecure->isChecked() ? strSecureO : strSecureX)
		+ strUse, 300, 180);
	m_alarm->show();

	disconnect(m_question, SIGNAL(yes()), this, SLOT(renew()));
	connect(m_alarm, SIGNAL(yes()), this, SLOT(finish()));
}

void DialogFormDeviceReturn::none()
{
	qDebug() << "none";
	m_question->hide();
}

void DialogFormDeviceReturn::finish()
{
	qDebug() << "finish";
	m_question->hide();
	m_alarm->hide();
	close();
}

void DialogFormDeviceReturn::notify(int row)
{
	m_employee = m->employees().at(row);
	edNameUserOrAdmin->setText(m_employee->nameUser());
	update();
}