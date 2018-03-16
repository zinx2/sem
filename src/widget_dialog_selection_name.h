#pragma once
#include "qheader.h"
#include "widget_dialog.h"
#include "sign_zone.h"
class WidgetDialogSelectionName : public WidgetDialog
{
	Q_OBJECT
public:
	//type 0:대출, 1:반
	explicit WidgetDialogSelectionName(int type, QString title, int width, int height, QWidget *parent = 0);

	public slots:
	void confirm();
	void cancel();
	void init();

private:
	QWidget* m_zoneName;
	QWidget* m_zoneUse;
	QWidget* m_zoneSecure;
	QWidget* m_zoneSign;

	QTextEdit* edName;
	QTextEdit* edUse;

	QCheckBox* cbSecure;

	SignZone* szSign;
};
