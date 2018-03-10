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
	void modal();

	void test1();
	void test2();
	void test3();
	void test4();
	void test5();

	void listDVIces();
	void listMNGements();
	void listEMPloyees();

	public slots:
	void textChanged();

private:
	QHBoxLayout* mainHBox;
	WidgetListDevices* wdLDVIces;
	WidgetListEmployees* wdLEMPloyees;
	WidgetListManagements* wdLMNGements;

	QTextEdit* textEdit;

	void clearItem();
};