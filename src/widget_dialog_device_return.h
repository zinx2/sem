#pragma once
#include "qheader.h"
#include "widget_dialog.h"
#include "sign_zone.h"

class WidgetDialogSignature; class Command;
class WidgetDialogDeviceReturn : public WidgetDialog
{
    Q_OBJECT
public:

    explicit WidgetDialogDeviceReturn(QString title, int width, int height, QWidget *parent = 0);

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

	WidgetDialogSignature* m_signature;

	bool doNext = false;
	int m_recognizationFinished = true;
};
