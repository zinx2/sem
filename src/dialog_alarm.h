#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"

class DialogAlarm : public WidgetDialog
{
	Q_OBJECT
public:
	explicit DialogAlarm(QString title, QString content, int width, int height, QWidget *parent = 0);

	void setMessage(QString txt);
	public slots:
	void confirm() override;

private:
	QWidget* m_zoneMessage;
	QLabel* m_lbMessage;
};