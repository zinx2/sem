#pragma once
#include "wrapped_widget.h"
class CommandProvider; class Command;
class WidgetMenu : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetMenu(QWidget *parent = 0);

	CommandProvider* commandProvider() { return m_commandProvider; }

	Command* btnBorrow() { return m_btnBorrow; }
	Command* btnReturn() { return m_btnReturn; }

	public slots:
	void resize();

private:
	int btnWidth = 0;

	QVBoxLayout* mainHBox;
	QWidget* mainWidget1;
	QWidget* mainWidget2;

	Command* m_btnBorrow;
	Command* m_btnReturn;

	CommandProvider* m_commandProvider;
};