#pragma once
#include "wrapped_widget.h"

class WidgetListManagements : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListManagements(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	//QScrollArea* scrollArea;

	public slots:
	void resize();
	void refresh();

private:
	QHBoxLayout* mainHBox;
	void updateTable();
};