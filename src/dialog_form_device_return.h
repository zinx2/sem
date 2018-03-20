#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogQuestion;
class DialogAlarm; class Command; class Employee;
class DialogFormDeviceReturn : public WidgetDialog
{
	Q_OBJECT
public:
    //type 0:대출, 1:반납
    explicit DialogFormDeviceReturn(int noDevice, QString title, int width, int height, QWidget *parent = 0);

	void setData(QString noAsset);
	void notify(int row);

	public slots:
	void confirm() override;
	void cancel() override;
    void init();
	void renew();
	void none();
	void finish();
	void activate();
	void search();


private:
	QTextEdit* edNameDevice;
	QTextEdit* edNoAsset;
	QTextEdit* edNameUserOrAdmin;
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

	int m_type;
	int m_noDevice;
};
