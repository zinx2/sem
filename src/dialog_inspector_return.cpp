﻿#include "dialog_inspector_return.h"
#include "dialog_form_device_return.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_networker.h"
DialogInspectorReturn::DialogInspectorReturn(QString title, int width, int height, QWidget *parent) : WidgetDialog(title, width, height, parent)
{
	setModal(true);
	Command* btnInit = new Command("init", "초기화", 70, 30);
	btnInit->setStyleSheet("background: #e1e1e1;");
	btnConfirm = new Command("confirm", "반납", 70, 30);
	btnConfirm->setStyleSheet("background: #e1e1e1;");
	btnConfirm->setEnabled(false);
	Command* btnCancel = new Command("cancel", "취소", 70, 30);
	btnCancel->setStyleSheet("background: #e1e1e1;");
	Command* btnSearch = new Command("search", "검색", 70, 30);
	btnSearch->setStyleSheet("background: #e1e1e1;");

	m_zoneBarcode = new QWidget(this);
	m_zoneBarcode->setLayout(new QVBoxLayout(m_zoneBarcode));
	m_zoneBarcode->setFixedSize(width, 60);
	m_zoneBarcode->layout()->setAlignment(Qt::AlignTop);
	m_zoneBarcode->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbBarcode = new QLabel("반납할 장비를 인식시켜 주세요.");
	lbBarcode->setFixedSize(width - 20, 25);
	lbBarcode->setAlignment(Qt::AlignBottom);
	m_zoneBarcode->layout()->addWidget(lbBarcode);
	edBarcode = new QTextEdit(this);
	edBarcode->setFixedSize(width - 50 - 70, 25);
	edBarcode->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	edBarcode->setStyleSheet("background: white;");
	edBarcode->setAlignment(Qt::AlignHCenter);
	//m_zoneBarcode->layout()->addWidget(edBarcode);
	//m_wdContents->layout()->addWidget(m_zoneBarcode);

	QWidget* subzoneBarcode = new QWidget(this);
	subzoneBarcode->setLayout(new QHBoxLayout(this));
	subzoneBarcode->layout()->setMargin(0);
	subzoneBarcode->layout()->setSpacing(5);
	subzoneBarcode->layout()->setAlignment(Qt::AlignLeft);
	subzoneBarcode->layout()->addWidget(edBarcode);
	subzoneBarcode->layout()->addWidget(btnSearch);
	m_zoneBarcode->layout()->addWidget(subzoneBarcode);
	m_wdContents->layout()->addWidget(m_zoneBarcode);

	m_zoneDevice = new QWidget(this);
	m_zoneDevice->setLayout(new QVBoxLayout(m_zoneDevice));
	m_zoneDevice->setFixedSize(width, 75);
	m_zoneDevice->layout()->setAlignment(Qt::AlignTop);
	m_zoneDevice->layout()->setContentsMargins(10, 0, 0, 0);
	QLabel* lbNameDevice = new QLabel("인식된 장비 :");
	lbNameDevice->setFixedSize(70, 25);
	lbNameDevice->setAlignment(Qt::AlignBottom);
	m_zoneDevice->layout()->addWidget(lbNameDevice);
	edNameDevice = new QLabel(m_zoneDevice);
	edNameDevice->setFixedSize(width - 20, 50);
	edNameDevice->setAlignment(Qt::AlignTop);
	m_zoneDevice->layout()->addWidget(edNameDevice);
	m_wdContents->layout()->addWidget(m_zoneDevice);

	m_wdTail->layout()->addWidget(btnInit);
	m_wdTail->layout()->addWidget(btnConfirm);
	m_wdTail->layout()->addWidget(btnCancel);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(btnSearch, SIGNAL(clicked()), this, SLOT(search()));
	//connect(edBarcode, SIGNAL(textChanged()), this, SLOT(recognize()));
	connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
	connect(m, SIGNAL(modalChanged()), this, SLOT(exit()));
	connect(m, SIGNAL(alarmedChanged()), this, SLOT(recognize()));
}
void DialogInspectorReturn::exit()
{
	close();
}
void DialogInspectorReturn::recognize()
{
	if (m->alarmed() && m->notificator()->type() == Notificator::DVIReturnedSearch)
	{
		bool result = m->notificator()->result();
		if (result)
		{
			Device* d = m->searchedDevice();
			QString aboutDevice = d->nameDevice() + "\n";
			aboutDevice += d->borrowed() ? "반납되지 않은 장비입니다." : "이미 반납된 장비입니다.";
			btnConfirm->setEnabled(d->borrowed()); /* 대출되지 않았을 때만 대출버튼 사용가능 */
			edNameDevice->setText(aboutDevice);
		}
		else
		{
			btnConfirm->setEnabled(false);
			edNameDevice->setText("검색된 장비가 없습니다.");
		}
		update();
		m->alarm(false);
	}
}
void DialogInspectorReturn::search()
{
	QString barcode = edBarcode->toPlainText();
	if (barcode.size() == 0) {
		edNameDevice->setText("자산번호를 입력해주세요.");
		return;
	}
	if (barcode.at(barcode.size() - 1) == '\n')
	{
		QStringRef subString(&barcode, 0, barcode.size() - 1);
		edBarcode->setText(subString.toString());
		edBarcode->setAlignment(Qt::AlignHCenter);
		barcode = subString.toString();
	}

	bool validate;
	int noDevice = barcode.toInt(&validate);
	if (validate)
		NetWorker::instance()->searchDeviceReturned(noDevice)->request();
	else
		edNameDevice->setText("유효하지 않은 자산번호입니다.");
}
void DialogInspectorReturn::confirm()
{
	DialogFormDeviceReturn* wddSignature = new DialogFormDeviceReturn(m_noDevice, "반납하기", 500, 540, this);
	wddSignature->setData(edBarcode->toPlainText());
	wddSignature->show();
}
void DialogInspectorReturn::cancel()
{
	close();
}
void DialogInspectorReturn::init()
{
	edNameDevice->setText("");
	edBarcode->setText("");
	edBarcode->setAlignment(Qt::AlignHCenter);
}
