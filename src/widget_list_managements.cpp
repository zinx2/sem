#include "widget_list_managements.h"
#include "networker.h"

WidgetListManagements::WidgetListManagements(QWidget *parent) : WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().testColor04);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);

	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);
	connect(d, SIGNAL(widthPageChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightPageChanged()), this, SLOT(resize()));


}

void WidgetListManagements::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
}