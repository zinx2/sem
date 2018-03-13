#pragma once
#include "qheader.h"


class Design; class Model;
class WidgetDialog : public QDialog
{
	Q_OBJECT
public:
	explicit WidgetDialog(QString title, int width, int height, QWidget *parent = 0);

protected:
	QWidget* m_wdContents;
	QWidget* m_wdTail;
	Design* d;
	Model* m;



};