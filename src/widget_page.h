#pragma once
#include "wrapped_widget.h"

class CommandProvider;  class Command;
class WidgetListDevices;
class WidgetListEmployees;
class WidgetListManagements;
class WidgetPage : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetPage(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QWidget* pgWidget = nullptr;
	public slots:
	void resize();
	void modal();
	void change(QString tag);

private:
	QHBoxLayout* mainHBox;
	WWidget* m_wdList;

	QWidget* m_wdCmds;
	QLabel* title(QString txt, int width);
	QLabel* m_lbTitle;

	void clearItem();
	void clearCommand();

};