#pragma once
#include "cs_qheader.h"
#include "widget_dialog.h"

class DialogFormDeviceBorrow; class Command;
class DialogSelectorPart : public WidgetDialog
{
	Q_OBJECT
public:
	//type 0:대출, 1:반
	explicit DialogSelectorPart(QString title, int width, int height, QWidget *parent = 0);

	void setParent(WidgetDialog* parent);

	public slots:
	void confirm() override;
	void cancel() override;
	void refresh();
	void activate();

private:
	QWidget* m_zoneParts;

	QTableWidget* m_table = nullptr;
	Command* btnConfirm;

	WidgetDialog* m_parent;

	int m_width;
	int m_height;

	void updateTable();
};
