#pragma once
#include "wrapped_widget.h"

class WidgetListEmployees : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListEmployees(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;

	public slots:
	void resize();

private:
	QHBoxLayout* mainHBox;
};