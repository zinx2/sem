#include "widget_page.h"

WidgetPage::WidgetPage(QWidget *parent) : WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().blue01);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);

	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);

	connect(d, SIGNAL(widthListChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(heightListChanged()), this, SLOT(resize()));
}

void WidgetPage::resize()
{
	mainWidget->setFixedWidth(d->widthPage());
	mainWidget->setFixedHeight(d->heightPage());
}
