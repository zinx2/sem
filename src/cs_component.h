#pragma once

#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
class CPTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	CPTextEdit(int width, QWidget *parent = 0) : QTextEdit(parent)
	{
		setFixedSize(width, 25);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setStyleSheet("background:white;");
		QFont f = font();
		f.setPointSize(10);
		setFont(f);
	}
	CPTextEdit* initHeight(int height) { setFixedHeight(height); return this; }
	CPTextEdit* initReadOnly(bool readOnley) { setReadOnly(readOnley); return this; }
	CPTextEdit* initText(QString txt) { setText(txt); return this; }
};

class CPLabel : public QLabel
{
	Q_OBJECT
public:
	CPLabel(int width, int height, QString txt, QWidget *parent = 0) : QLabel(txt, parent)
	{
		setFixedSize(width, height);
		setAlignment(Qt::AlignVCenter | Qt::AlignRight);
		//setStyleSheet("background:white;");
		//QFont f = font();
		//f.setPointSize(10);
		//setFont(f);
	}
	CPLabel* initAlignment(Qt::Alignment alignment) { setAlignment(alignment); return this; }
	CPLabel* initContentsMargins(int left, int right, int top, int bottom)
	{
		setContentsMargins(left, top, right, bottom);
		return this;
	}
};

class CPWidget : public QWidget
{
	Q_OBJECT
public:
	CPWidget(int width, int height, QLayout* ly, QWidget *parent = 0) : QWidget(parent)
	{
		setFixedSize(width, height);
		setLayout(ly);
		layout()->setAlignment(Qt::AlignVCenter);
		layout()->setSpacing(5);
		layout()->setMargin(0);
	}
	CPWidget* initContentsMargins(int left, int right, int top, int bottom)
	{
		setContentsMargins(left, top, right, bottom);
		return this;
	}
	CPWidget* initAlignment(Qt::Alignment alignment) 
	{ 
		layout()->setAlignment(alignment); 
		return this; 
	}
	CPWidget* initEnabled(bool enabled)
	{
		setEnabled(enabled);
		return this;
	}
	CPWidget* append(QWidget* w)
	{
		layout()->addWidget(w);
		return this;
	}

};