#pragma once
#include "qheader.h"
#include "design.h"
class Command : public QPushButton
{
public:
	Command(QString tag, QString name, int width, int height) : m_tag(tag)
	{
		this->setFixedSize(width, height);
		QFont font = this->font();
		font.setPointSize(10);
		this->setFont(font);
		this->setText(name);
	}
	QString tag() { return m_tag; }
private:
	QString m_tag;
};

class CommandProvider : public QObject
{
public:
	CommandProvider()
	{
		d = Design::instance();
	}
	void releaseAll()
	{
		foreach(Command* c, m_commands)
		{
			c->setStyleSheet(d->c().btnReleasedStyle);
		}
	}
	void select(QString tag)
	{
		releaseAll();
		foreach(Command* c, m_commands)
		{
			if (!c->tag().compare(tag))
			{
				c->setStyleSheet(d->c().btnSelectedStyle);
			}
		}
	}
	void append(Command* command)
	{
		command->setStyleSheet(d->c().btnReleasedStyle);
		m_commands.append(command);
	}
	Command* command(QString tag)
	{
		foreach(Command* c, m_commands)
		{
			if (!c->tag().compare(tag))
			{
				return c;
			}
		}
		return nullptr;
	}
private:
	QList<Command*> m_commands;
	Design* d;
};