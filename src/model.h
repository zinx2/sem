#pragma once
#include "qheader.h"
#define BTN_DEVICE_LIST "devicelist"
#define BTN_DEVICE_MANAGE_LIST "devicemanagelist"
#define BTN_EMPLOYEE_MANAGE_LIST "employeemanagelist"

class Device : public QObject {
	Q_OBJECT
		Q_PROPERTY(int noDevice READ noDevice WRITE setNoDevice NOTIFY noDeviceChanged)
		Q_PROPERTY(QString nameDevice READ nameDevice WRITE setNameDevice NOTIFY nameDeviceChanged)
		Q_PROPERTY(QString noAsset READ noAsset WRITE setNoAsset NOTIFY noAssetChanged)
		Q_PROPERTY(QString barcode READ barcode WRITE setBarcode NOTIFY barcodeChanged)
		Q_PROPERTY(QString price READ price WRITE setPrice NOTIFY priceChanged)
		Q_PROPERTY(QString dateTaked READ dateTaked WRITE setDateTaked NOTIFY dateTakedChanged)
		Q_PROPERTY(QString memo READ memo WRITE setMemo NOTIFY memoChanged)
		Q_PROPERTY(bool borrowed READ borrowed WRITE borrow NOTIFY borrowedChanged)
public:
	int noDevice() const { return m_noDevice; }
	QString nameDevice() const { return m_nameDevice; }
	QString noAsset() const { return m_noAsset; }
	QString barcode() const { return m_barcode; }
	QString price() const { return m_price; }
	QString dateTaked() const { return m_dateTaked; }
	QString memo() const { return m_memo; }
	bool borrowed() const { return m_borrowed; }

	public slots:
	void setNoDevice(const int m) { m_noDevice = m; emit noDeviceChanged(); }
	void setNameDevice(const QString &m) { m_nameDevice = m; emit nameDeviceChanged(); }
	void setNoAsset(const QString &m) { m_noAsset = m; emit noAssetChanged(); }
	void setBarcode(const QString &m) { m_barcode = m; emit barcodeChanged(); }
	void setPrice(const QString &m) { m_price = m; emit priceChanged(); }
	void setDateTaked(const QString &m) { m_dateTaked = m; emit dateTakedChanged(); }
	void setMemo(const QString &m) { m_memo = m; emit memoChanged(); }
	void borrow(bool m) { m_borrowed = m; emit borrowedChanged(); };

signals:
	void noDeviceChanged();
	void nameDeviceChanged();
	void userChanged();
	void noAssetChanged();
	void barcodeChanged();
	void priceChanged();
	void dateTakedChanged();
	void memoChanged();
	void borrowedChanged();

private:
	int m_noDevice = -1;
	QString m_nameDevice;
	QString m_noAsset;
	QString m_barcode;
	QString m_price;
	QString m_dateTaked;
	QString m_memo;
	bool m_borrowed = false;
};

class Rent : public QObject {
	Q_OBJECT
		Q_PROPERTY(int noRent READ noRent WRITE setNoRent NOTIFY noRentChanged)
		Q_PROPERTY(int noDevice READ noDevice WRITE setNoDevice NOTIFY noDeviceChanged)
		Q_PROPERTY(QString noAsset READ noAsset WRITE setNoAsset NOTIFY noAssetChanged)
		Q_PROPERTY(QString nameDevice READ nameDevice WRITE setNameDevice NOTIFY nameDeviceChanged)
		Q_PROPERTY(QString nameUser READ nameUser WRITE setNameUser NOTIFY nameUserChanged)
		Q_PROPERTY(QString nameAdmin READ nameAdmin WRITE setNameAdmin NOTIFY nameAdminChanged)
		Q_PROPERTY(QString dateBorrowed READ dateBorrowed WRITE setDateBorrowed NOTIFY dateBorrowedChanged)
		Q_PROPERTY(QString dateReturned READ dateReturned WRITE setDateReturned NOTIFY dateReturnedChanged)
		Q_PROPERTY(QString signUser READ signUser WRITE setSignUser NOTIFY signUserChanged)
		Q_PROPERTY(QString signAdmin READ signAdmin WRITE setSignAdmin NOTIFY signAdminChanged)
		Q_PROPERTY(bool completed READ completed WRITE complete NOTIFY completedChanged)
public:
	int noRent() const { return m_noRent; }
	int noDevice() const { return m_noDevice; }
	QString noAsset() const { return m_noAsset; }
	QString nameDevice() const { return m_nameDevice; }
	QString nameUser() const { return m_nameUser; }
	QString nameAdmin() const { return m_nameAdmin; }
	QString dateBorrowed() const { return m_dateBorrowed; }
	QString dateReturned() const { return m_dateReturned; }
	QString signUser() const { return m_signUser; }
	QString signAdmin() const { return m_signAdmin; }
	bool completed() const { return m_completed; }

	public slots:
	void setNoRent(const int m) { m_noRent = m; emit noRentChanged(); }
	void setNoDevice(const int m) { m_noDevice = m; emit noAssetChanged(); }
	void setNoAsset(const QString &m) { m_noAsset = m; emit noDeviceChanged(); }
	void setNameDevice(const QString &m) { m_nameDevice = m; emit nameDeviceChanged(); }
	void setNameUser(const QString &m) { m_nameUser = m; emit nameUserChanged(); }
	void setNameAdmin(const QString &m) { m_nameAdmin = m; emit nameAdminChanged(); }
	void setDateBorrowed(const QString &m) { m_dateBorrowed = m; emit dateBorrowedChanged(); }
	void setDateReturned(const QString &m) { m_dateReturned = m; emit dateReturnedChanged(); }
	void setSignUser(const QString &m) { m_signUser = m; emit signUserChanged(); }
	void setSignAdmin(const QString &m) { m_signAdmin = m; emit signAdminChanged(); }
	void complete(bool m) { m_completed = m; emit completedChanged(); };

signals:
	void noRentChanged();
	void noAssetChanged();
	void noDeviceChanged();
	void nameDeviceChanged();
	void nameUserChanged();
	void nameAdminChanged();
	void dateBorrowedChanged();
	void dateReturnedChanged();
	void signUserChanged();
	void signAdminChanged();
	void completedChanged();

private:
	int m_noRent = -1;
	int m_noDevice = -1;
	QString m_noAsset;
	QString m_nameDevice;
	QString m_nameUser;
	QString m_nameAdmin;
	QString m_dateBorrowed;
	QString m_dateReturned;
	QString m_signUser;
	QString m_signAdmin;
	bool m_completed = false;
};

class Part : public QObject {
	Q_OBJECT
		Q_PROPERTY(int noPart READ noPart WRITE setNoPart NOTIFY noPartChanged)
		Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
		Q_PROPERTY(bool system READ system WRITE isSystem NOTIFY systemChanged)
public:
	int noPart() const { return m_noPart; }
	QString namePart() const { return m_namePart; }
	bool system() const { return m_system; }

	public slots :
	void setNoPart(const int m) { m_noPart = m; emit noPartChanged(); }
	void setNamePart(const QString &m) { m_namePart = m; emit namePartChanged(); }
	void isSystem(const bool m) { m_system = m; emit systemChanged(); }

signals:
	void noPartChanged();
	void namePartChanged();
	void systemChanged();

private:
	int m_noPart = -1;
	QString m_namePart;
	bool m_system = false;
};

class Employee : public QObject {
	Q_OBJECT
		Q_PROPERTY(int noUser READ noUser WRITE setNoUser NOTIFY noUserChanged)
		Q_PROPERTY(QString nameUser READ nameUser WRITE setNameUser NOTIFY nameUserChanged)
		Q_PROPERTY(bool manager READ manager WRITE isManager NOTIFY isManagerChanged)
public:
	int noUser() const { return m_noUser; }
	QString nameUser() const { return m_nameUser; }
	bool manager() const { return m_manager; }

	public slots :
	void setNoUser(const int m) { m_noUser = m; emit noUserChanged(); }
	void setNameUser(const QString &m) { m_nameUser = m; emit nameUserChanged(); }
	void isManager(const bool m) { m_manager = m; emit isManagerChanged(); }

signals:
	void noUserChanged();
	void nameUserChanged();
	void isManagerChanged();

private:
	int m_noUser = -1;
	QString m_nameUser;
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
		Q_PROPERTY(bool modal READ modal WRITE setModal NOTIFY modalChanged)
		Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
		Q_PROPERTY(int scaledItemWidth READ scaledItemWidth WRITE setScaledItemWidth NOTIFY scaledItemWidthChanged)
		Q_PROPERTY(int scaledItemHeight READ scaledItemHeight WRITE setScaledItemHeight NOTIFY scaledItemHeightChanged)
		Q_PROPERTY(int itemFixedWidth READ itemFixedWidth WRITE setItemFixedWidth NOTIFY itemFixedWidthChanged)
		Q_PROPERTY(int itemFixedHeight READ itemFixedHeight WRITE setItemFixedHeight NOTIFY itemFixedHeightChanged)

		Q_PROPERTY(QList<Device*> devices READ devices WRITE setDevices NOTIFY devicesChanged)
		Q_PROPERTY(QList<Part*> parts READ parts WRITE setParts NOTIFY partsChanged)
		Q_PROPERTY(QList<Employee*> employees READ employees WRITE setEmployees NOTIFY employeesChanged)
		Q_PROPERTY(QList<Rent*> rents READ rents WRITE setRents NOTIFY rentsChanged)

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

	QList<Rent*> rents() { return m_rents; }
	int countRent() { return m_rents.size(); }

	QString message() const { return m_message; }
	int selectedItem() const { return m_selectedItem; }
	QString path() const { return m_path; }
	QString dir() const { return m_dir; }
	QString log() const { return m_log; }
	QString date() const { return m_date; }
	bool full() const { return m_full; }
	bool pressedCtrl() const { return m_pressedCtrl; }
	bool modal() const { return m_modal; }
	qreal scale() const { return m_scale; }
	int scaledItemWidth() const { return m_scaledItemWidth; }
	int scaledItemHeight() const { return m_scaledItemHeight; }
	int itemFixedWidth() const { return m_itemFixedWidth; }
	int itemFixedHeight() const { return m_itemFixedHeight; }

	public slots:
    void setDevices(QList<Device*> m) { m_devices.clear(); m_devices = m; emit devicesChanged(); }
	void setParts(QList<Part*> m) { m_parts.clear();  m_parts = m; emit partsChanged(); }
	void setEmployees(QList<Employee*> m) { m_employees.clear();  m_employees = m; emit employeesChanged(); }
	void setRents(QList<Rent*> m) { m_rents.clear();  m_rents = m; emit rentsChanged(); }
	void setMessage(QString m) { m_message = m; emit messageChanged(); }
	void selectItem(int m) { m_selectedItem = m; emit itemSelected(); }
	void setPath(QString m) { m_path = m; emit pathChanged(); }
	void setDir(QString m) { m_dir = m; emit dirChanged(); }
	void setLog(QString m) { m_log = m; emit logChanged(); }
	void setDate(QString m) { m_date = m; emit dateChanged(); }
	void setFull(bool m) { m_full = m; emit fullChanged(); }
	void pressCtrl(bool m) { m_pressedCtrl = m; emit pressedCtrlChanged(); }
	void setModal(bool m) { m_modal = m; emit modalChanged(); }
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
	void modalChanged();
	void scaleChanged();
	void scaledItemWidthChanged();
	void scaledItemHeightChanged();
	void itemFixedWidthChanged();
	void itemFixedHeightChanged();

	void devicesChanged();
	void partsChanged();
	void employeesChanged();
	void rentsChanged();

private:
	QList<Device*> m_devices;
	QList<Part*> m_parts;
	QList<Employee*> m_employees;
	QList<Rent*> m_rents;
	QString m_message;
	int m_selectedItem;
	QString m_path;
	QString m_dir;
	QString m_log;
	QString m_date;
	bool m_full = false;
	bool m_pressedCtrl = false;
	bool m_modal = false;
	qreal m_scale = 1;
	int m_scaledItemWidth = 720;
	int m_scaledItemHeight = 1080;
	int m_itemFixedWidth = 720;
	int m_itemFixedHeight = 1280;
};
