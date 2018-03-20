#pragma once
#include "wrapped_widget.h"

class NetWorker; class DialogQuestion; class CPWidget; class Command; class CPLabel;
class WidgetListDevices : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListDevices(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	QWidget* m_wdNavi;
	Command* m_cmdPrev;
	Command* m_cmdNext;
	CPLabel* m_lbCnt;

	//QScrollArea* scrollArea;
	public slots:
	void resize();
	void refresh();
	void openDialogToAdd();
	void openDialogToRemove();
	void openDialogToEdit();
	void deviceRemove();
	void closeDialogToRemove();
	void prev();
	void next();

signals:
	void onClicked();
private:
	QHBoxLayout* mainHBox;
	void updateTable();

	NetWorker* m_net;
	DialogQuestion* m_question;
	QString getCountDevice();
};