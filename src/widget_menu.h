#pragma once
#include "wrapped_widget.h"

class WidgetMenu : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetMenu(QWidget *parent = 0);
	QPushButton* btnDeviceList() { return m_btnDeviceList; }
	QPushButton* btnDeviceManagementList() { return m_btnDeviceManagementList; }
	QPushButton* btnEmployeeManagementList() { return m_btnEmployeeManagementList; }
	QPushButton* btnBorrow() { return m_btnBorrow; }
	QPushButton* btnReturn() { return m_btnReturn; }

	public slots:
	void resize();

private:
	QHBoxLayout* mainHBox;
	QWidget* mainWidget1;
	QWidget* mainWidget2;

	QPushButton* m_btnDeviceList;
	QPushButton* m_btnDeviceManagementList;
	QPushButton* m_btnEmployeeManagementList;
	QPushButton* m_btnBorrow;
	QPushButton* m_btnReturn;

	QPushButton* createButton(QString name);
};