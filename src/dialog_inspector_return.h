#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogFormDeviceReturn; class Command;
class DialogInspectorReturn : public WidgetDialog
{
    Q_OBJECT
public:

    explicit DialogInspectorReturn(QString title, int width, int height, QWidget *parent = 0);

	public slots:
	void confirm() override;
	void cancel() override;
	void init();
	void recognize();
	void exit();
	void search();

private:
	QWidget* m_zoneBarcode;
	QWidget* m_zoneDevice;

	QTextEdit* edBarcode;
	QLabel* edNameDevice;
	Command* btnConfirm;

	DialogFormDeviceReturn* m_signature;

	bool doNext = false;
	int m_recognizationFinished = true;
	int m_noDevice = -1;
};
