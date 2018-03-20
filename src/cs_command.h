#pragma once
#include "cs_qheader.h"
#include "cs_design.h"
#include <QStyle>
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
	Command* initStyleSheet(QString sheet) { setStyleSheet(sheet); return this; }
	Command* initIcon(QString iconPath) {
		QPixmap pixmap(iconPath);
		QIcon icon(pixmap);
		setIcon(icon);
		setIconSize(pixmap.rect().size());
		return this;
	};
	Command* initIcon(QString iconPath, QString txt) {
		QPixmap pixmap(iconPath);
		m_pixmap = pixmap;
		m_txt = txt;
		return this;
	};
	QPixmap m_pixmap;
	QString m_txt;
	void paintEvent(QPaintEvent* e)
	{
		QPushButton::paintEvent(e);

		if (!m_pixmap.isNull())
		{
			const int y = (height() - m_pixmap.height()) / 2; // add margin if needed
			QPainter painter(this);
			painter.drawPixmap(10, y, m_pixmap); // hardcoded horizontal margin
			painter.drawText(40, height()/2 + 5, m_txt);
		}
	}
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

	QList<Command*> commands() { return m_commands; }
private:
	QList<Command*> m_commands;
	Design* d;
};
