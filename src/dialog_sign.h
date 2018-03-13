#pragma once
#include "qheader.h"

#define WIDTH_SIGN_ZONE 480
#define HEIGHT_SIGN_ZONE 200

class Model;
class SignZone;
class DialogSign : public QDialog
{
	Q_OBJECT

public:
	explicit DialogSign(QWidget *parent = 0);

	public slots:
	void off();
	void save();

signals:
	void saved();

private:
	Model* m;
	SignZone* signZone;
};
