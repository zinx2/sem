#pragma once
#include "qheader.h"
#include "design.h"
#include "model.h"

class Design; class Model;
class WWidget : public QWidget {
	Q_OBJECT
public:
	explicit WWidget(QWidget *parent = 0) : QWidget(parent) {
		d = Design::instance();
		m = Model::instance();
	}
protected:
	Design* d;
	Model* m;

	void msg(QString message) { m->setMessage(message); }
};