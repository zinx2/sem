#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Design; class Model;
class WidgetMenu; class WidgetPage; class DialogAlarm;
class DialogInspectorBorrow; class DialogInspectorReturn;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	public slots:
	void initializeUI();
	void resize();
	void listDVIces();
	void listMNGements();
	void listEMPloyees();
	void listDVIcesWithPageInit();
	void listMNGementsWithPageInit();
	void listEMPloyeesWithPageInit();
	void doBorrow();
	void doReturn();
	void updatePage();

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	bool initedUI = false;
	Design* d;
	Model* m;
    Ui::MainWindow *ui;
	QWidget* frameMenu;
	QWidget* framePage;

	WidgetMenu* widgetMenu;
	WidgetPage* widgetPage;
	DialogAlarm* m_alarm;
	DialogInspectorBorrow* m_inspectorBorrow;
	DialogInspectorReturn* m_inspectorReturn;

	void setWidget(QWidget* w, QRect geometry, QString color);
	void connections();

};

#endif // MAINWINDOW_H
