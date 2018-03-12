#include "widget_dialog.h"
#include "design.h"
#include "model.h"

WidgetDialog::WidgetDialog(QString title, int width, int height, QWidget *parent) : QDialog(parent)
{
	d = Design::instance();
	m = Model::instance();

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setFixedWidth(width); setFixedHeight(height);
	setStyleSheet("background: #eeeeee;");
	setLayout(new QVBoxLayout(this));
	layout()->setAlignment(Qt::AlignTop);
	layout()->setSpacing(0);
	layout()->setMargin(0);

	QWidget* wdTitle = new QWidget(this);
	wdTitle->setFixedWidth(width); wdTitle->setFixedHeight(25);
	wdTitle->setStyleSheet("background: #2b78e4;");
	wdTitle->setLayout(new QVBoxLayout(this));
	wdTitle->layout()->setAlignment(Qt::AlignCenter);
	layout()->addWidget(wdTitle);
	QLabel* lbTitle = new QLabel(title, this);
	lbTitle->setStyleSheet("color:white");
	wdTitle->layout()->addWidget(lbTitle);

	m_wdContents = new QWidget(this);
	layout()->addWidget(m_wdContents);
	m_wdContents->setFixedWidth(width); m_wdContents->setFixedHeight(height - 75);
	m_wdContents->setStyleSheet("background: transparent; border:0px; ");

	m_wdTail = new QWidget(this);
	layout()->addWidget(m_wdTail);
	m_wdTail->setFixedWidth(width); m_wdTail->setFixedHeight(50);
	m_wdTail->setLayout(new QHBoxLayout(this));
	m_wdTail->layout()->setMargin(0);
	m_wdTail->layout()->setSpacing(0);



	//Command* btnCancel = new Command("cancel", "Ãë¼Ò", width, 50);
	//btnCancel->setStyleSheet("color: white; background: #2b78e4;");
	//m_wdTail->layout()->addWidget(btnCancel);


	//connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

//void WidgetDialog::confirm()
//{
//	qDebug() << "confirm";
//}
//void WidgetDialog::cancel()
//{
//	qDebug() << "cancel";
//}