#pragma once
#include "wrapped_widget.h"

class WidgetListDevices : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListDevices(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	//QScrollArea* scrollArea;

	public slots:
	void resize();
	void refresh();
	void deviceAdd();
	void deviceRemove();
	void deviceEdit();

private:
	QHBoxLayout* mainHBox;
	void updateTable();
};