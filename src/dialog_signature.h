#pragma once
#include "cs_qheader.h"
#define SIZE_PEN 3
#define WIDTH_SIGN_ZONE 480
#define HEIGHT_SIGN_ZONE 200

//class Model;
//class SignZone;
//class DialogSign : public QDialog
//{
//	Q_OBJECT
//
//public:
//	explicit DialogSign(QWidget *parent = 0);
//
//	public slots:
//	void off();
//	void save();
//
//signals:
//	void saved();
//
//private:
//	Model* m;
//	SignZone* signZone;
//};

class PaintScene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit PaintScene(int width, int height, QObject *parent = 0);


private:
	QPointF     previousPoint;     
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

class DialogSignature : public QGraphicsView
{
	Q_OBJECT
public:
	explicit DialogSignature(QWidget *parent = 0);
	void toImage();

	void init();
private:
	int width;
	int height;
};