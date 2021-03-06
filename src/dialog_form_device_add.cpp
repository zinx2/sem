﻿#include "dialog_form_device_add.h"
#include "dialog_alarm.h"
#include "dialog_question.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_networker.h"
#include "dialog_selector_part.h"
#include "cs_component.h"
DialogFormDeviceAdd::DialogFormDeviceAdd(QString title, int width, int height, QWidget *parent)
	: WidgetDialog(title, width, height, parent)
{
	m_net = NetWorker::instance();
	setModal(true);
	btnConfirm = new Command("confirm", "확인", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");
	btnConfirm->setEnabled(false);
	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");
	Command* btnSaerch = new Command("search", "부서찾기", 70, 30);
	btnSaerch->setStyleSheet("background: #e1e1e1;");
	Command* btnInit = new Command("init", "초기화", 70, 30);
	btnInit->setStyleSheet("background: #e1e1e1;");

	m_lbMessage = new QLabel("장비명을 입력해주세요.");
	m_lbMessage->setFixedSize(width - 250, 25);
	m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	m_wdTail->layout()->addWidget(m_lbMessage);

	m_wdTail->layout()->addWidget(btnInit);
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);
	m_wdContents->setContentsMargins(0, 5, 0, 0);

	m_edNameDevice = new CPTextEdit(200, this);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, "장비명"))
		->append(m_edNameDevice));

	m_edNoAsset = new CPTextEdit(200, this);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, "자산번호"))
		->append(m_edNoAsset));

	m_edPart = (new CPTextEdit(200, this))->initReadOnly(true)->initText("시스템파트");
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, "소속파트"))
		->append(m_edPart)
		/*->append(btnSaerch)*/);

	m_edPrice = new CPTextEdit(200, this);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, "취득금액"))
		->append(m_edPrice));

	m_edDate = new CPTextEdit(200, this);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, "취득일자"))
		->append(m_edDate));

	m_edMemo = (new CPTextEdit(width - 75, this))->initHeight(50);
	m_wdContents->layout()->addWidget(
		(new CPWidget(width, 60, new QHBoxLayout, this))
		->initContentsMargins(10, 10, 0, 0)
		->append((new CPLabel(50, 50, "비고"))->initAlignment(Qt::AlignTop | Qt::AlignRight)->initContentsMargins(0, 0, 5, 0))
		->append(m_edMemo));

	height = 35 * 5  + 5 + 95;
	m_wdContents->setFixedHeight(height);
	setFixedHeight(height + 10);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(m_edNameDevice, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(m_edNoAsset, SIGNAL(textChanged()), this, SLOT(recognize()));
	connect(m_edPart, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(m_edPrice, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(m_edDate, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(m_edMemo, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(btnSaerch, SIGNAL(clicked()), this, SLOT(search()));
	connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
}
void DialogFormDeviceAdd::search()
{
	DialogSelectorPart* selection = new DialogSelectorPart("부서찾기", 400, 500, this);
	selection->setParent(this);
	selection->show();
}
void DialogFormDeviceAdd::recognize()
{
	QString barcode = m_edNoAsset->toPlainText();
	if (barcode.size() == 0) {
		activate();
		return;
	}
	if (barcode.at(barcode.size() - 1) == '\n')
	{
		QStringRef subString(&barcode, 0, barcode.size() - 1);
		m_edNoAsset->setText(subString.toString());
		barcode = subString.toString();
	}

	int searchedCnt = 0;
	foreach(Device* d, m->devices())
	{
		if (!d->noAsset().compare(barcode))
		{
			searchedCnt++;
			m_lbMessage->setText("이미 등록된 장비입니다.");
			btnConfirm->setEnabled(false);
			return;
		}
	}
	if (searchedCnt == 0)
	{
		m_lbMessage->setText("등록 가능한 장비입니다.");
		btnConfirm->setDisabled(
			m_edNameDevice->toPlainText().isEmpty() ||
			m_edNoAsset->toPlainText().isEmpty() ||
			m_edPart->toPlainText().isEmpty() ||
			m_edPrice->toPlainText().isEmpty() ||
			m_edDate->toPlainText().isEmpty());
	}
	QTextCursor tmpCursor = m_edNoAsset->textCursor();
	m_edNoAsset->moveCursor(QTextCursor::EndOfLine);
}
void DialogFormDeviceAdd::activate()
{
	btnConfirm->setDisabled(
		m_edNameDevice->toPlainText().isEmpty() ||
		m_edNoAsset->toPlainText().isEmpty() ||
		m_edPart->toPlainText().isEmpty() ||
		m_edPrice->toPlainText().isEmpty() ||
		m_edDate->toPlainText().isEmpty());

	if (m_edNameDevice->toPlainText().isEmpty())
	{
		m_lbMessage->setText("장비명을 입력해주세요.");
	}
	else if (m_edNoAsset->toPlainText().isEmpty())
	{
		m_lbMessage->setText("자산번호를 입력해주세요.");
	}
	else if (m_edPrice->toPlainText().isEmpty())
	{
		m_lbMessage->setText("취득금액을 입력해주세요.");
	}
	else if (m_edDate->toPlainText().isEmpty())
	{
		m_lbMessage->setText("취득일을 입력해주세요.");
	}
	else 
	{
		m_lbMessage->setText("");
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

	QString strNameDevice = "장비명 : " + m_edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + m_edNoAsset->toPlainText() + "\n";
	QString strPart = "소속파트 : " + m_edPart->toPlainText() + "\n";
	QString strPrice = "취득금액 : " + m_edPrice->toPlainText() + "\n";
	QString strDate = "취득일자 : " + m_edDate->toPlainText() + "\n";
	QString strMemo = "비고 : " + m_edMemo->toPlainText() + "\n";

	m_question = new DialogQuestion(
		"알림",
		"장비를 추가하시겠습니까?\n\n"
		+ strNameDevice
		+ strNoAsset
		+ strPart
		+ strPrice
		+ strDate
		+ strMemo, 300, 180);
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
void DialogFormDeviceAdd::allow()
{
	qDebug() << "allow";
	QString strNameDevice = "장비명 : " + m_edNameDevice->toPlainText() + "\n";
	QString strNoAsset = "자산번호 : " + m_edNoAsset->toPlainText() + "\n";
	QString strPart = "소속파트 : " + m_edPart->toPlainText() + "\n";
	QString strPrice = "취득금액 : " + m_edPrice->toPlainText() + "\n";
	QString strDate = "취득일자 : " + m_edDate->toPlainText() + "\n";
	QString strMemo = "비고 : " + m_edMemo->toPlainText() + "\n";

	m_net->addDevice(
		1/*m_part->noPart()*/,
		m_edNameDevice->toPlainText(),
		m_edNoAsset->toPlainText(),
		m_edNoAsset->toPlainText(),
		m_edPrice->toPlainText(),
		m_edDate->toPlainText(),
		m_edMemo->toPlainText())->request();

	disconnect(m_question, SIGNAL(yes()), this, SLOT(allow()));

	m_question->close();
	close();
}

void DialogFormDeviceAdd::none()
{
	qDebug() << "none";
	m_question->hide();
}
void DialogFormDeviceAdd::notify(int row)
{
	m_part = m->parts().at(row);
	m_edPart->setText(m_part->namePart());
	update();
}

void DialogFormDeviceAdd::init()
{
	m_edNameDevice->setText("");
	m_edNoAsset->setText("");
	m_edPrice->setText("");
	m_edDate->setText("");
	m_edMemo->setText("");
	m_edNameDevice->setText("");
}
