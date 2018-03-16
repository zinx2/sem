#include "dialog_signature.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_networker.h"
#include "cs_qheader.h"
DialogSignature::DialogSignature(QWidget *parent)  : QGraphicsView(parent)
{

	width = parent->width();// -horizontalScrollBar()->height();
	height = parent->height();// -verticalScrollBar()->width();
	setFixedWidth(width); setFixedHeight(height);
	setScene(new PaintScene(width, height, this));
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setStyleSheet("background: white; border: 1px solid #7a7a7a");
	setContentsMargins(0, 0, 0, 0);
}

void DialogSignature::init()
{
	setScene(new PaintScene(width, height, this));
}
bool DialogSignature::toImage()
{
	QString fileName = QDir::currentPath() + "/tmp.png";
	QPixmap pixMap = QPixmap::grabWidget(this);
	return pixMap.save(fileName);
}

PaintScene::PaintScene(int width, int height, QObject *parent) : QGraphicsScene(parent) 
{ 
	setSceneRect(QRectF(0, 0, width, height));
}
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


//DialogSign::DialogSign(QWidget *parent) : QDialog(parent)
//{
//	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//	setFixedWidth(WIDTH_SIGN_ZONE + 20);
//	setFixedHeight(HEIGHT_SIGN_ZONE + 100);
//
//	setLayout(new QVBoxLayout(this));
//	layout()->setSpacing(10);
//
//	QLabel* lb = new QLabel(this);
//	lb->setText("서명을 해주세요.");
//	layout()->addWidget(lb);
//
//	QWidget* zoneSign = new QWidget(this);
//	zoneSign->setFixedWidth(WIDTH_SIGN_ZONE);
//	zoneSign->setFixedHeight(HEIGHT_SIGN_ZONE);
//	zoneSign->setStyleSheet("background: #eeeeee; border: 0px solid black");
//	zoneSign->setLayout(new QHBoxLayout);
//	zoneSign->setContentsMargins(0, 0, 0, 0);
//	zoneSign->layout()->setMargin(0);
//
//	//QWidget* xx = new QWidget(this);
//	//xx->setFixedWidth(100);
//	//xx->setFixedHeight(100);
//	//xx->setLayout(new QHBoxLayout);
//	//xx->setStyleSheet("background: #00ff00; border: 1px solid black");
//
//	signZone = new SignZone(this);
//	//xx->layout()->addWidget(signZone);
//	zoneSign->layout()->addWidget(signZone);
//	//zoneSign->layout()->addWidget(xx)
//	/*signZone = new SignZone(this);
//	zoneSign->layout()->addWidget(signZone);
//	layout()->addWidget(zoneSign);*/
//
//	//QWidget* zoneBtn = new QWidget(this);
//	//zoneBtn->setLayout(new QHBoxLayout(this));
//	//layout()->addWidget(zoneBtn);
//
//	//Command* cmdConfirm = new Command("confirm", "확인", 235, 45);
//	//zoneBtn->layout()->addWidget(cmdConfirm);
//	//Command* cmdCancel = new Command("cancel", "취소", 235, 45);
//	//zoneBtn->layout()->addWidget(cmdCancel);
//	//zoneBtn->layout()->setAlignment(Qt::AlignCenter);
//	//zoneBtn->setContentsMargins(0, 0, 0, 0);
//	//zoneBtn->layout()->setMargin(0);
//
//	//connect(cmdCancel, SIGNAL(clicked()), this, SLOT(off()));
//	//connect(cmdConfirm, SIGNAL(clicked()), this, SLOT(save()));
//
//	m = Model::instance();
//}
//void DialogSign::save()
//{
//	if (signZone->toImage())
//	{
//		NetWorker* n = NetWorker::getInstance();
//		QString filePath = QDir::currentPath() + "/tmp.png";
//		n->uploadFile(filePath)->request();
//		off();
//	}
//	emit saved();
//}
//void DialogSign::off()
//{
//	close();
//	//m->setModal(false);
//}