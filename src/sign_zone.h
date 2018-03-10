#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#define SIZE_PEN 3

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

class SignZone : public QGraphicsView
{
	Q_OBJECT
public:
	explicit SignZone(QWidget *parent = 0);
	bool toImage();
};