#pragma once
#include "wrapped_widget.h"

class WidgetListManagements : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListManagements(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;

	public slots:
	void resize();

private:
	QHBoxLayout* mainHBox;
};