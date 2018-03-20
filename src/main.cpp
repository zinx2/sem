#include "widget_mainwindow.h"
#include <QApplication>
#include <QtCore/QTextCodec>
#include <QLabel>
static QString qkor(const char *strKor)
{
	static QTextCodec *codec = QTextCodec::codecForName("eucKR");
	return codec->toUnicode(strKor);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

