#pragma once
#include "qheader.h"
#include "widget_dialog.h"

class WidgetDialogAlarm : public WidgetDialog
{
	Q_OBJECT
public:
	explicit WidgetDialogAlarm(QString title, int width, int height, QWidget *parent = 0);

	public slots:
	void confirm();

private:
	QWidget* m_wdContents;
};