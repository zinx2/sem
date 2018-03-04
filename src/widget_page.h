#pragma once
#include "wrapped_widget.h"

class WidgetPage : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetPage(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QWidget* utilWidget;
	public slots:
	void resize();

private:
	QHBoxLayout* mainHBox;
};