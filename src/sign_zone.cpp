#include "sign_zone.h"
#include "qheader.h"
SignZone::SignZone(QWidget *parent)  : QGraphicsView(parent)
{
	int width = parent->width() - 20;
	int height = parent->height();
	setFixedWidth(width); setFixedHeight(height);
	setScene(new PaintScene(width, height, this));
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
bool SignZone::toImage()
{
	QString fileName = QDir::currentPath() + "/tmp.png";
	QPixmap pixMap = QPixmap::grabWidget(this);
	return pixMap.save(fileName);
}

PaintScene::PaintScene(int width, int height, QObject *parent) : QGraphicsScene(parent) 
{ 
	setSceneRect(QRectF(0, 0, width, height));
};
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	// When you press the mouse button, draw the ellipse

	addEllipse(event->scenePos().x() - 5,
		event->scenePos().y() - 5,
		SIZE_PEN,
		SIZE_PEN,
		QPen(Qt::NoPen),
		QBrush(Qt::black));
	// Save the coordinates of the point of pressing
	previousPoint = event->scenePos();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	// We draw the line with the previous coordinates
	addLine(previousPoint.x(),
		previousPoint.y(),
		event->scenePos().x(),
		event->scenePos().y(),
		QPen(Qt::black, SIZE_PEN, Qt::SolidLine, Qt::RoundCap));
	// Update on the previous coordinate data
	previousPoint = event->scenePos();
}

