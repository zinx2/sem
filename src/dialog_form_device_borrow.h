#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogQuestion; 
class DialogAlarm; class Command; class Employee; class NetWorker;
class CPTextEdit; class CPWidget;
class DialogFormDeviceBorrow : public WidgetDialog
{
	Q_OBJECT
public:
    //type 0:대출, 1:반납
    explicit DialogFormDeviceBorrow(QString title, int width, int height, QWidget *parent = 0);

	void setData(QString noAsset);
	void notify(int row);

	public slots:
	void confirm() override;
	void cancel() override;
    void init();
	void allow();
	void none();
	void finish();
	void activate();
	void search();
	void alarm(bool isSuccess);
	void sign(bool isSuccess);

private:
	CPTextEdit* edNameDevice;
	CPTextEdit* edNoAsset;
	CPTextEdit* edNameUserOrAdmin;
	QTextEdit* edDateBorrowedOrReturned;
	QTextEdit* edUse;

	QLabel* m_lbMessage;

	QRadioButton* rbYes;
	QRadioButton* rbNo;
	Command* btnConfirm;

	DialogSignature* szSign;
	DialogAlarm* m_alarm;
	DialogQuestion* m_question;

	Employee* m_employee;
	NetWorker* m_net;
	void error(QString message);
	int m_type;
};
