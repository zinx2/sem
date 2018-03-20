#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogQuestion;
class DialogAlarm; class Command; class Part; class NetWorker;
class CPTextEdit; class Device;
class DialogFormDeviceEdit : public WidgetDialog
{
	Q_OBJECT
public:
	//type 0:대출, 1:반납
	explicit DialogFormDeviceEdit(int row, QString title, int width, int height, QWidget *parent = 0);

	void setData(QString noAsset);
	void notify(int row);

	public slots:
	void confirm() override;
	void cancel() override;
	void allow();
	void none();
	void activate();
	void recognize();
	void search();
	void check(int state);
	void init();

private:
	CPTextEdit* m_edNameDevice;
	CPTextEdit* m_edNoAsset;
	CPTextEdit* m_edPart;
	CPTextEdit* m_edPrice;
	CPTextEdit* m_edDate;
	CPTextEdit* m_edMemo;

	QLabel* m_lbMessage;

	QCheckBox* cbSecure;
	Command* btnConfirm;

	DialogQuestion* m_question;

	Part* m_part;
	Device* m_device;
	NetWorker* m_net;
	bool notified = false;
	void error(QString message);

	QMutex m_mtx;
};
