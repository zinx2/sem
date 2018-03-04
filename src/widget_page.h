#pragma once
#include "wrapped_widget.h"

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
	QWidget* pgWidget;
	public slots:
	void resize();

	void test1();
	void test2();
	void test3();
	void test4();

	void listDVIces();
	void listMNGements();
	void listEMPloyees();

private:
	QHBoxLayout* mainHBox;
	WidgetListDevices* wdLDVIces;
	WidgetListEmployees* wdLEMPloyees;
	WidgetListManagements* wdLMNGements;

	void clearItem();
};