﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "design.h"
#include "model.h"
#include "widget_menu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	d = Design::instance();
	this->setMinimumSize(d->MIM_WINDOW_WIDTH, d->MIM_WINDOW_HEIGHT);
	this->setGeometry(QRect(100, 100, d->widthWindow(), d->heightWindow()));
    ui->setupUi(this);
	
	frameMenu = ui->widget_menu;
	frameList = ui->widget_list;
	frameUtil = ui->widget_util;

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
	w = d->widthMenu(); d->setWidthMenu(w);
	h = geo.height();
	frameMenu->setGeometry(x, y, w, h);
	widgetMenu->setGeometry(0, 0, w, h);
}

void MainWindow::setWidget(QWidget* w, QRect geometry, QString color)
{
	w->setGeometry(geometry);
	w->setStyleSheet("background-color:" + color);
}

void MainWindow::connections()
{
	connect(widgetMenu->btnDeviceList(), SIGNAL(clicked()), this, SLOT(deviceList()));
	connect(widgetMenu->btnDeviceManagementList(), SIGNAL(clicked()), this, SLOT(deviceManagementList()));
	connect(widgetMenu->btnEmployeeManagementList(), SIGNAL(clicked()), this, SLOT(employeeManagementList()));
	connect(widgetMenu->btnBorrow(), SIGNAL(clicked()), this, SLOT(borrow()));
	connect(widgetMenu->btnReturn(), SIGNAL(clicked()), this, SLOT(_return()));
}

void MainWindow::deviceList()
{

}

void MainWindow::deviceManagementList()
{

}

void MainWindow::employeeManagementList()
{

}

void MainWindow::borrow()
{

}

void MainWindow::_return()
{

}