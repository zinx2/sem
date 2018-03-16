#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"

class DialogQuestion : public WidgetDialog
{
	Q_OBJECT
public:
	explicit DialogQuestion(QString title, QString content, int width, int height, QWidget *parent = 0);

	public slots:
	void confirm() override;
	void cancel() override;
	void reject();
	//void closeEvent(QCloseEvent *e) override;


private:
	QWidget* m_zoneMessage;
};