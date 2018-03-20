#pragma once
#include "cs_qheader.h"


class Design; class Model;
class WidgetDialog : public QDialog
{
	Q_OBJECT
public:
	explicit WidgetDialog(QString title, int width, int height, QWidget *parent = 0);

	virtual void notify(int index){};

	public slots:
	virtual void confirm(){};
	virtual void cancel(){};

signals:
	void yes();
	void no();

protected:
	QWidget* m_wdContents;
	QWidget* m_wdTail;
	Design* d;
	Model* m;
};