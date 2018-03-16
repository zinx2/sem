#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogQuestion; 
class DialogAlarm; class Command; class Employee; class NetWorker;
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
	void check(int state);
	void alarm(bool isSuccess);
	void sign(bool isSuccess);

private:
	QWidget* m_zoneDevice;
	QWidget* m_zoneName;
	QWidget* m_zoneUse;
	QWidget* m_zoneSecure;
	QWidget* m_zoneSign;

	QTextEdit* edNameDevice;
	QTextEdit* edNoAsset;
	QTextEdit* edNameUserOrAdmin;
	QTextEdit* edDateBorrowedOrReturned;
	QTextEdit* edUse;

	QLabel* m_lbMessage;

	QCheckBox* cbSecure;
	Command* btnConfirm;

	DialogSignature* szSign;
	DialogAlarm* m_alarm;
	DialogQuestion* m_question;

	Employee* m_employee;
	NetWorker* m_net;
	void error(QString message);
	int m_type;
};
