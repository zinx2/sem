#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "design.h"
#include "model.h"
#include "widget_menu.h"
#include "widget_page.h"
#include "networker.h"
#include "command.h"
#include "sign_zone.h"
#include "widget_dialog_alarm.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	d = Design::instance();
	this->setMinimumSize(d->MIM_WINDOW_WIDTH, d->MIM_WINDOW_HEIGHT);
	//this->setMaximumSize(d->MAX_WINDOW_WIDTH, d->MAX_WINDOW_HEIGHT);
	this->setGeometry(QRect(100, 100, d->widthWindow(), d->heightWindow()));
    ui->setupUi(this);
	frameMenu = ui->widget_menu;
	framePage = ui->widget_list;

	m = Model::instance();
	ui->centralWidget->setStyleSheet("background-color:" + d->c().grary01);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *e)
{
	if (!initedUI) {
		initializeUI();
		return;
	}

	QSize newSize = e->size();
	QSize oldSize = e->oldSize();
	d->setWidthWindow(newSize.width());
	d->setHeightWindow(newSize.height());

	resize();

}
void MainWindow::initializeUI()
{
	int x = 0; int y = 0; int w = 0; int h = 0;
	w = d->widthMenu(); h = d->heightMenu();	
	setWidget(frameMenu, QRect(x, y, w, h), d->c().grary01);
	widgetMenu = new WidgetMenu(frameMenu);
	QVBoxLayout* vBoxMenubar = new QVBoxLayout(frameMenu);
	vBoxMenubar->setMargin(0);
	vBoxMenubar->addWidget(widgetMenu);
	connect(widgetMenu, SIGNAL(onSign()), this, SLOT(sign()));

	x += d->widthMenu(); w = d->widthPage(); h = d->heightPage();
	setWidget(framePage, QRect(x, y, w, h), d->c().testColor02);
	widgetPage = new WidgetPage(framePage);
	QVBoxLayout* vBoxList = new QVBoxLayout(framePage);
	vBoxList->setMargin(0);
	vBoxList->addWidget(widgetPage);

	resize();
	connections();
	initedUI = true;
}
void MainWindow::resize()
{
	int x = 0; int y = 0; int w = 0; int h = 0;
	QRect geo;

	geo = frameMenu->geometry();
	x = 0;
	y = 0;
	w = geo.width(); // d->widthWindow(); d->setWidthMenu(w);
	h = d->heightWindow(); d->setHeightMenu(h);//geo.height();
	frameMenu->setGeometry(x, y, w, h);
	widgetMenu->setGeometry(0, 0, w, h);

	geo = framePage->geometry();
	x = d->widthMenu();
	y = 0;
	w = d->widthWindow() - d->widthMenu(); d->setWidthPage(w);
	h = d->heightWindow(); d->setHeightPage(h);
	framePage->setGeometry(x, y, w, h);
	widgetPage->setGeometry(0, 0, w, h);
}

void MainWindow::setWidget(QWidget* w, QRect geometry, QString color)
{
	w->setGeometry(geometry);
	w->setStyleSheet("background-color:" + color);
}

void MainWindow::connections()
{
	connect(widgetMenu->commandProvider()->command(BTN_DEVICE_LIST), SIGNAL(clicked()), this, SLOT(listDVIces()));
	connect(widgetMenu->commandProvider()->command(BTN_DEVICE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listMNGements()));
	connect(widgetMenu->commandProvider()->command(BTN_EMPLOYEE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listEMPloyees()));
	connect(widgetMenu->btnBorrow(), SIGNAL(clicked()), this, SLOT(doBorrow()));
	connect(widgetMenu->btnReturn(), SIGNAL(clicked()), this, SLOT(doReturn()));
}

void MainWindow::listDVIces()
{
	widgetPage->listDVIces();
	widgetMenu->commandProvider()->select(BTN_DEVICE_LIST);
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_LIST), SIGNAL(clicked()), this, SLOT(listDVIces()));
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listMNGements()));
	//connect(widgetMenu->commandProvider()->command(BTN_EMPLOYEE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listEMPloyees()));
}

void MainWindow::listMNGements()
{
	widgetPage->listMNGements();
	widgetMenu->commandProvider()->select(BTN_DEVICE_MANAGE_LIST);
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_LIST), SIGNAL(clicked()), this, SLOT(listDVIces()));
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listMNGements()));
	//connect(widgetMenu->commandProvider()->command(BTN_EMPLOYEE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listEMPloyees()));
}

void MainWindow::listEMPloyees()
{
	widgetPage->listEMPloyees();
	widgetMenu->commandProvider()->select(BTN_EMPLOYEE_MANAGE_LIST);
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_LIST), SIGNAL(clicked()), this, SLOT(listDVIces()));
	//connect(widgetMenu->commandProvider()->command(BTN_DEVICE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listMNGements()));
	//connect(widgetMenu->commandProvider()->command(BTN_EMPLOYEE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listEMPloyees()));
}

void MainWindow::doBorrow()
{

}

void MainWindow::doReturn()
{

}

void MainWindow::sign()
{
	m->setModal(true);
	/*DialogSign* dg = new DialogSign(this);
	dg->show();*/

	WidgetDialogAlarm* dg = new WidgetDialogAlarm("알림", 300, 300, this);
	dg->show();
}