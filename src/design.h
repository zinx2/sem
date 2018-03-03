#pragma once
#include <QObject>
#include <QScreen>
#include <QDebug>
#include <QGuiApplication>

/* Main Window Size */
//#define MIM_WINDOW_WIDTH  pt(960)
//#define MIM_WINDOW_HEIGHT pt(720)
//#define MAX_WINDOW_WIDTH  pt(1920)
//#define MAX_WINDOW_HEIGHT pt(1080)

class Colors {
public:
	const QString grary01 = "#eeeeee";
	const QString blue01 = "#2b78e4";
	const QString blue02 = "#6fa8dc";
};

class Design : public QObject {
	Q_OBJECT
		Q_PROPERTY(int widthWindow  READ widthWindow  WRITE setWidthWindow NOTIFY widthWindowChanged)
		Q_PROPERTY(int heightWindow READ heightWindow WRITE setHeightWindow NOTIFY heightWindowChanged)
		Q_PROPERTY(int widthMenu  READ widthMenu  WRITE setWidthMenu  NOTIFY widthMenuChanged)
		Q_PROPERTY(int heightMenu READ heightMenu WRITE setHeightMenu NOTIFY heightMenuChanged)
		Q_PROPERTY(int widthList READ widthList  WRITE setWidthList  NOTIFY widthListChanged)
		Q_PROPERTY(int heightList READ heightList WRITE setHeightList NOTIFY heightListChanged)
		Q_PROPERTY(int widthUtil READ widthUtil  WRITE setWidthUtil  NOTIFY widthUtilChanged)
		Q_PROPERTY(int heightUtil READ heightUtil WRITE setHeightUtil NOTIFY heightUtilChanged)

private:
	Design();
	static Design* m_instance;
	Colors m_colors;
public:
	static Design* instance() {
		if (m_instance == nullptr) m_instance = new Design();
		return m_instance;
	}
	Colors c() { return m_colors; }

	const int MIM_WINDOW_WIDTH = 1080;
	const int MIM_WINDOW_HEIGHT = 720;
	const int MAX_WINDOW_WIDTH = 1920;
	const int MAX_WINDOW_HEIGHT = 1080;

	int widthWindow() const { return m_widthWindow; }
	int heightWindow() const { return m_heightWindow; }
	int widthMenu() const { return m_widthMenu; }
	int heightMenu() const { return m_heightMenu; }
	int widthList() const { return m_widthList; }
	int heightList() const { return m_heightList; }
	int widthUtil() const { return m_widthUtil; }
	int heightUtil() const { return m_heightUtil; }
	void initialize();

	public slots:
	int pt(int pixel) { return pixel * scaleFactor; }
	void setWidthWindow(const int &m) { m_widthWindow = m;  emit widthWindowChanged(); }
	void setHeightWindow(const int &m) { m_heightWindow = m; emit heightWindowChanged(); }
	void setWidthMenu(const int &m) { m_widthMenu = m; emit widthMenuChanged(); }
	void setHeightMenu(const int &m) { m_heightMenu = m; emit heightMenuChanged(); }
	void setWidthList(const int &m) { m_widthList = m; emit widthListChanged(); }
	void setHeightList(const int &m) { m_heightList = m; emit heightListChanged(); }
	void setWidthUtil(const int &m) { m_widthUtil = m; emit widthUtilChanged(); }
	void setHeightUtil(const int &m) { m_heightUtil = m; emit heightUtilChanged(); }

signals:
	void widthWindowChanged();
	void heightWindowChanged();
	void widthMenuChanged();
	void heightMenuChanged();
	void widthListChanged();
	void heightListChanged();
	void widthUtilChanged();
	void heightUtilChanged();

private:

	float scaleFactor = 1;
	int m_widthWindow = MIM_WINDOW_WIDTH;
	int m_heightWindow = MIM_WINDOW_HEIGHT;
	int m_widthMenu = m_widthWindow;
	int m_heightMenu = 50;

	int m_widthUtil = m_widthWindow;
	int m_heightUtil = pt(100);

	int m_widthList = m_widthWindow;
	int m_heightList = m_heightWindow - m_heightMenu - m_heightUtil;
};
//extern Design D;

