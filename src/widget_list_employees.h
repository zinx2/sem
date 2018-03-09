#pragma once
#include "wrapped_widget.h"
#include "command.h"
class WidgetListEmployees : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetListEmployees(QWidget *parent = 0);
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTableWidget* table = nullptr;
	QScrollArea* scrollArea;

	public slots:
	void resize();
	void refresh();
	void test()
	{
		qDebug() << "test";
	}
	void ccc(int row, int col)
	{
		qDebug() << row << "/" << col;
	}
	void b(QTableWidgetItem* it)
	{
		//qDebug() << row << "/" << col;
	}

private:
	QHBoxLayout* mainHBox;
	void updateTable();

	CommandProvider* m_commandProvider;
	QList<Command*> list;
};