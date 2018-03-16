#pragma once
#include "wrapped_widget.h"
#include "cs_command.h"
class WidgetListEmployees : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListEmployees(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	QScrollArea* scrollArea;

	public slots:
	void resize();
	void refresh();

private:
	QHBoxLayout* mainHBox;
	void updateTable();

	CommandProvider* m_commandProvider;
	QList<Command*> list;
};