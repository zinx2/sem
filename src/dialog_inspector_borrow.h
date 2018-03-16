#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"
#include "dialog_signature.h"

class DialogFormDeviceBorrow; class Command;
class DialogInspectorBorrow : public WidgetDialog
{
    Q_OBJECT
public:

	explicit DialogInspectorBorrow(QString title, int width, int height, QWidget *parent = 0);

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

	DialogFormDeviceBorrow* m_signature;

	bool doNext = false;
	int m_recognizationFinished = true;
};
