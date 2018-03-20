#pragma once
#include "wrapped_widget.h"

class NetWorker; class DialogQuestion; class CPWidget; class Command; class CPLabel;
class WidgetListManagements : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListManagements(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	QWidget* m_wdNavi;
	Command* m_cmdPrev;
	Command* m_cmdNext;
	CPLabel* m_lbCnt;

	public slots:
	void resize();
	void refresh();
	void prev();
	void next();

private:
	QHBoxLayout* mainHBox;
	void updateTable();

	QString getCountDevice();
};