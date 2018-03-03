#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Design; class Model;
class WidgetMenu;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	public slots:
	void initializeUI();
	void resize();
	void deviceList();
	void deviceManagementList();
	void employeeManagementList();
	void borrow();
	void _return();

protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	bool initedUI = false;
	Design* d;
	Model* m;
    Ui::MainWindow *ui;
	QWidget* frameMenu;
	QWidget* frameList;
	QWidget* frameUtil;

	WidgetMenu* widgetMenu;

	void setWidget(QWidget* w, QRect geometry, QString color);
	void connections();

};

#endif // MAINWINDOW_H
