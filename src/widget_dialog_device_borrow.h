#pragma once
#include "qheader.h"
#include "widget_dialog.h"
#include "sign_zone.h"

class WidgetDialogSignature; class Command;
class WidgetDialogDeviceBorrow : public WidgetDialog
{
    Q_OBJECT
public:

	explicit WidgetDialogDeviceBorrow(QString title, int width, int height, QWidget *parent = 0);

	public slots:
	void confirm() override;
	void cancel() override;
	void init();
	void recognize();
	void exit();

private:
	QWidget* m_zoneBarcode;
	QWidget* m_zoneDevice;

	QTextEdit* edBarcode;
	QLabel* edNameDevice;
	Command* btnConfirm;
	Command* btnSearch;

	WidgetDialogSignature* m_signature;

	bool doNext = false;
	int m_recognizationFinished = true;
};
