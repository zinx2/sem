#pragma once
#include "wrapped_widget.h"

class WidgetListDevices : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListDevices(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;

	public slots:
	void resize();

private:
	QHBoxLayout* mainHBox;
};