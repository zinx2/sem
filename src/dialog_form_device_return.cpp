#include "dialog_form_device_return.h"
#include "dialog_alarm.h"
#include "dialog_question.h"
#include "dialog_selector_employee.h"
#include "cs_networker.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_component.h"
DialogFormDeviceReturn::DialogFormDeviceReturn(int noDevice, QString title, int width, int height, QWidget *parent)
    : WidgetDialog(title, width, height, parent)
{
	m_noDevice = noDevice;
	setModal(true);
    btnConfirm = new Command("confirm", "확인", 70, 30);
    btnConfirm->setStyleSheet("background: #e1e1e1;");
    Command* btnCancel = new Command("cancel", "취소", 70, 30);
    btnCancel->setStyleSheet("background: #e1e1e1;");
    Command* btnSaerch = new Command("search", "직원찾기", 70, 25);
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

	Device* dv = m->searchedDevice();

	/* ROW 1 */
	edNameDevice = (new CPTextEdit(200, this))->initReadOnly(true)->initText(dv->nameDevice());
	edNoAsset = (new CPTextEdit(170, this))->initReadOnly(true)->initText(dv->noAsset());
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout))
		->initContentsMargins(10, 0, 10, 0)
		->append(new CPLabel(35, 25, "장비명"))
		->append(edNameDevice)
		->append(new CPLabel(60, 25, "자산번호"))
		->append(edNoAsset));

	/* ROW 2 */
	edNameUserOrAdmin = (new CPTextEdit(130, this))->initReadOnly(true);
	edDateBorrowedOrReturned = (new CPTextEdit(170, this))->initReadOnly(true)->initText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout))
		->initContentsMargins(10, 0, 10, 0)
		->append(new CPLabel(35, 25, "확인자"))
		->append(edNameUserOrAdmin)
		->append(btnSaerch)
		->append(new CPLabel(55, 25, "반납일"))
		->append(edDateBorrowedOrReturned));

	/* ROW 3 */
	edUse = (new CPTextEdit(width - 60, this))->initHeight(50)->initReadOnly(true)->initText(dv->memo());
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 60, new QHBoxLayout))
		->initContentsMargins(10, 0, 10, 0)
		->append((new CPLabel(35, 60, "용도"))->initAlignment(Qt::AlignTop | Qt::AlignRight))
		->append(edUse));

	/* ROW 4 */
	rbYes = new QRadioButton("예", this);
	rbYes->setFixedWidth(50);
	rbNo = new QRadioButton("아니오", this);
	rbNo->setFixedWidth(70);
	rbNo->setChecked(true);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout))
		->initContentsMargins(10, 0, 10, 0)
		->append((new CPLabel(130, 25, "보안점검(초기화) 여부"))->initAlignment(Qt::AlignVCenter | Qt::AlignLeft))
		->append(rbYes)
		->append(rbNo));

	/* ROW 5 */
	szSign = new DialogSignature(this);
	szSign->setFixedSize(width - 20, 175);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 210, new QVBoxLayout))
		->initContentsMargins(10, 0, 0, 0)
		->append((new CPLabel(70, 25, "서명"))->initAlignment(Qt::AlignBottom))
		->append(szSign));

	height = 35 + 75 + 35 + 210 + 35;
	m_wdContents->setFixedHeight(height);
	setFixedHeight(height + 35);

    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(edNameDevice, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edNoAsset, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edNameUserOrAdmin, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(edDateBorrowedOrReturned, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(rbYes, SIGNAL(pressed()), this, SLOT(activate()));
	connect(rbNo, SIGNAL(pressed()), this, SLOT(activate()));
	connect(edUse, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(btnSaerch, SIGNAL(clicked()), this, SLOT(search()));
    connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
}
void DialogFormDeviceReturn::search()
{
	DialogSelectorEmployee* selection = new DialogSelectorEmployee("직원 찾기", 400, 500, true, this);
	selection->setParent(this);
	selection->show();
}
void DialogFormDeviceReturn::activate()
{
	btnConfirm->setDisabled(edNameDevice->toPlainText().isEmpty() ||
		edNoAsset->toPlainText().isEmpty() ||
		edNameUserOrAdmin->toPlainText().isEmpty() ||
        edDateBorrowedOrReturned->toPlainText().isEmpty());

	if (edNameUserOrAdmin->toPlainText().isEmpty())
	{
		m_lbMessage->setText("확인자를 선택해주세요.");
    }
	else
	{
		m_lbMessage->setText("서명을 해주세요.");
	}
}
void DialogFormDeviceReturn::setData(QString noAsset)
{
	foreach(Device* d, m->devices())
	{
		if (!d->noAsset().compare(noAsset))
		{
			edNameDevice->setText(d->nameDevice());
			edNoAsset->setText(d->noAsset());
			edUse->setText(d->memo());
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
	QString strNameUser = "확인자 : " + edNameUserOrAdmin->toPlainText() + "\n";
	QString strUse = "용도 : " + edUse->toPlainText() + "\n";

	QString strSecureO = rbYes->isChecked() ? "보안점검 : O\n" : "";
	QString strSecureX = rbNo->isChecked() ? "보안점검 : X\n" : "";

	m_question = new DialogQuestion(
		"알림",
        "반납하시겠습니까?\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strDate
		+ strNameUser
		+ strSecureO + strSecureX
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
	NetWorker::instance()->returnDevice(
		edNoAsset->toPlainText(),
		m_employee->noUser(),
		m_noDevice,
		rbYes->isChecked())->request();

	m_question->hide();
	close();

	//파일 업로드
	//사인 전송
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

void DialogFormDeviceReturn::notify(int noUser)
{
	foreach(Employee* e, m->employees())
	{
		if (noUser == e->noUser())
		{
			m_employee = e;
			break;
		}
	}
	edNameUserOrAdmin->setText(m_employee->nameUser());
	update();
}
