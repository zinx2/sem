#pragma once
#include "qheader.h"
class Device : public QObject {
	Q_OBJECT
		Q_PROPERTY(int no READ no WRITE setNo NOTIFY noChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString assetNo READ assetNo WRITE setAssetNo NOTIFY assetNoChanged)
		Q_PROPERTY(QString barcode READ barcode WRITE setBarcode NOTIFY barcodeChanged)
		Q_PROPERTY(QString price READ price WRITE setPrice NOTIFY priceChanged)
		Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
		Q_PROPERTY(QString memo READ memo WRITE setMemo NOTIFY memoChanged)
		Q_PROPERTY(bool borrowed READ borrowed WRITE borrow NOTIFY borrowedChanged)
public:
	int no() const { return m_no; }
	QString name() const { return m_name; }
	QString assetNo() const { return m_assetNo; }
	QString barcode() const { return m_barcode; }
	QString price() const { return m_price; }
	QString date() const { return m_date; }
	QString memo() const { return m_memo; }
	bool borrowed() const { return m_borrowed; }

	public slots:
	void setNo(const int m) { m_no = m; }
	void setName(const QString &m) { m_name = m; emit nameChanged(); }
	void setAssetNo(const QString &m) { m_assetNo = m; emit assetNoChanged(); }
	void setBarcode(const QString &m) { m_barcode = m; emit barcodeChanged(); }
	void setPrice(const QString &m) { m_price = m; emit priceChanged(); }
	void setDate(const QString &m) { m_date = m; emit dateChanged(); }
	void setMemo(const QString &m) { m_memo = m; emit memoChanged(); }
	void borrow(bool m) { m_borrowed = m; emit borrowedChanged(); };

signals:
	void noChanged();
	void nameChanged();
	void assetNoChanged();
	void barcodeChanged();
	void priceChanged();
	void dateChanged();
	void memoChanged();
	void borrowedChanged();

private:
	int m_no = -1;
	QString m_name;
	QString m_assetNo;
	QString m_barcode;
	QString m_price;
	QString m_date;
	QString m_memo;
	bool m_borrowed = false;
};

class Part : public QObject {
	Q_OBJECT
		Q_PROPERTY(int no READ no WRITE setNo NOTIFY noChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(bool system READ system WRITE isSystem NOTIFY systemChanged)
public:
	int no() const { return m_no; }
	QString name() const { return m_name; }
	bool system() const { return m_system; }

	public slots:
	void setNo(const int m) { m_no = m; }
	void setName(const QString &m) { m_name = m; emit nameChanged(); }
	void isSystem(const bool m) { m_system = m; emit systemChanged(); }

signals:
	void noChanged();
	void nameChanged();
	void systemChanged();

private:
	int m_no = -1;
	QString m_name;
	bool m_system = false;
};

class Employee : public QObject {
	Q_OBJECT
		Q_PROPERTY(int no READ no WRITE setNo NOTIFY noChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(bool manager READ manager WRITE isManager NOTIFY isManagerChanged)
public:
	int no() const { return m_no; }
	QString name() const { return m_name; }
	bool manager() const { return m_manager; }

	public slots :
	void setNo(const int m) { m_no = m; }
	void setName(const QString &m) { m_name = m; emit nameChanged(); }
	void isManager(const bool m) { m_manager = m; emit isManagerChanged(); }

signals:
	void noChanged();
	void nameChanged();
	void isManagerChanged();

private:
	int m_no = -1;
	QString m_name;
	bool m_manager = false;
};

class Model : public QObject {
	Q_OBJECT
		Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
		Q_PROPERTY(int selectedItem READ selectedItem WRITE selectItem NOTIFY itemSelected)
		Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
		Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
		Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
		Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
		Q_PROPERTY(bool full READ full WRITE setFull NOTIFY fullChanged)
		Q_PROPERTY(bool pressedCtrl READ pressedCtrl WRITE pressCtrl NOTIFY pressedCtrlChanged)
		Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
		Q_PROPERTY(int scaledItemWidth READ scaledItemWidth WRITE setScaledItemWidth NOTIFY scaledItemWidthChanged)
		Q_PROPERTY(int scaledItemHeight READ scaledItemHeight WRITE setScaledItemHeight NOTIFY scaledItemHeightChanged)
		Q_PROPERTY(int itemFixedWidth READ itemFixedWidth WRITE setItemFixedWidth NOTIFY itemFixedWidthChanged)
		Q_PROPERTY(int itemFixedHeight READ itemFixedHeight WRITE setItemFixedHeight NOTIFY itemFixedHeightChanged)

		Q_PROPERTY(QList<Device*> devices READ devices WRITE setDevices NOTIFY devicesChanged)
		Q_PROPERTY(QList<Part*> parts READ parts WRITE setParts NOTIFY partsChanged)
		Q_PROPERTY(QList<Employee*> employees READ employees WRITE setEmployees NOTIFY employeesChanged)

private:
	Model() { };
	static Model* m_instance;
public:
	static Model* instance() {
		if (m_instance == nullptr) m_instance = new Model();
		return m_instance;
	}

	QList<Device*> devices() { return m_devices; }
	int countDevice() { return m_devices.size(); }

	QList<Part*> parts() { return m_parts; }
	int countPart() { return m_parts.size(); }

	QList<Employee*> employees() { return m_employees; }
	int countEmployee() { return m_employees.size(); }

	QString message() const { return m_message; }
	int selectedItem() const { return m_selectedItem; }
	QString path() const { return m_path; }
	QString dir() const { return m_dir; }
	QString log() const { return m_log; }
	QString date() const { return m_date; }
	bool full() const { return m_full; }
	bool pressedCtrl() const { return m_pressedCtrl; }
	qreal scale() const { return m_scale; }
	int scaledItemWidth() const { return m_scaledItemWidth; }
	int scaledItemHeight() const { return m_scaledItemHeight; }
	int itemFixedWidth() const { return m_itemFixedWidth; }
	int itemFixedHeight() const { return m_itemFixedHeight; }

	public slots:
	void setDevices(QList<Device*> m) { m_devices.clear(); m_devices = m; emit devicesChanged(); }
	void setParts(QList<Part*> m) { m_parts.clear();  m_parts = m; emit partsChanged(); }
	void setEmployees(QList<Employee*> m) { m_employees.clear();  m_employees = m; emit employeesChanged(); }
	void setMessage(QString m) { m_message = m; emit messageChanged(); }
	void selectItem(int m) { m_selectedItem = m; emit itemSelected(); }
	void setPath(QString m) { m_path = m; emit pathChanged(); }
	void setDir(QString m) { m_dir = m; emit dirChanged(); }
	void setLog(QString m) { m_log = m; emit logChanged(); }
	void setDate(QString m) { m_date = m; emit dateChanged(); }
	void setFull(bool m) { m_full = m; emit fullChanged(); }
	void pressCtrl(bool m) { m_pressedCtrl = m; emit pressedCtrlChanged(); }
	void setScale(qreal m) { m_scale = m; emit scaleChanged(); }
	void setScaledItemWidth(int m) { m_scaledItemWidth = m; emit scaledItemWidthChanged(); }
	void setScaledItemHeight(int m) { m_scaledItemHeight = m; emit scaledItemHeightChanged(); }
	void setItemFixedWidth(int m) { m_itemFixedWidth = m; emit itemFixedWidthChanged(); }
	void setItemFixedHeight(int m) { m_itemFixedHeight = m; emit itemFixedHeightChanged(); }

signals:
	void messageChanged();
	void itemSelected();
	void pathChanged();
	void dirChanged();
	void logChanged();
	void dateChanged();
	void dirRemove();
	void dirRefresh();
	void logClear();
	void zoomIn();
	void zoomOut();
	void fullChanged();
	void pressedCtrlChanged();
	void scaleChanged();
	void scaledItemWidthChanged();
	void scaledItemHeightChanged();
	void itemFixedWidthChanged();
	void itemFixedHeightChanged();

	void devicesChanged();
	void partsChanged();
	void employeesChanged();

private:
	QList<Device*> m_devices;
	QList<Part*> m_parts;
	QList<Employee*> m_employees;
	QString m_message;
	int m_selectedItem;
	QString m_path;
	QString m_dir;
	QString m_log;
	QString m_date;
	bool m_full = false;
	bool m_pressedCtrl = false;
	qreal m_scale = 1;
	int m_scaledItemWidth = 720;
	int m_scaledItemHeight = 1080;
	int m_itemFixedWidth = 720;
	int m_itemFixedHeight = 1280;
};