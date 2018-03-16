#pragma once

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QUrlQuery>
#include "cs_model.h"
#include <QImage>
#include <QQueue>

typedef std::function<void()> FUNC;
class NetHost : public QObject {
	Q_OBJECT
public:
	NetHost(QString type, QString addr, QUrlQuery queries, FUNC func)
		: m_type(type), m_addr(addr), m_queries(queries), m_func(func) { }
	NetHost(QString type, QString addr, FUNC func)
		: m_type(type), m_addr(addr), m_func(func) { }
	QString type() const { return m_type; }
	QString addr() const { return m_addr; }
	QUrlQuery queries() const { return m_queries; }
	FUNC func() const { return m_func; }

	public slots :
	void setType(const QString &m) { m_type = m; }
	void setAddr(const QString &m) { m_addr = m; }
	void setQueries(const QUrlQuery &m) { m_queries = m; }
	void setFunc(const FUNC &m) { m_func = m;}

private:
	QString m_type;
	QString m_addr;
	QUrlQuery m_queries;
	FUNC m_func;
};

class NetWorker : public QObject
{
	Q_OBJECT
public:
	static NetWorker* instance()
	{
		if (m_instance == nullptr)
			m_instance = new NetWorker();
		return m_instance;
	}


	//void requestGET(QNetworkRequest req, FUNC parser);
	//void requestPOST(QNetworkRequest req, FUNC parser);

	void clearBuf() { m_hosts.clear(); }

	public slots:
	void request();
	void httpError(QNetworkReply::NetworkError msg);

	/************* API CALL METHODS ****************/
	void getDemoAll();
	void getDemo(int id);
	void postDemoAll();
	void postDemo(int id);

	NetWorker* getUserList();
	NetWorker* getPartList();
	NetWorker* getDeviceList(int noPart = 1, int searchType = 0, int now = 1);
	NetWorker* getRentList(int noPart = 1, int now = 1);

	NetWorker* borrowDevice(QString barcode, int noUser, QString purpose, QString imgPath= QDir::currentPath() + "/tmp.png");
	NetWorker* returnDevice(int barcode, int noAdmin, bool isInitial=false);
	NetWorker* signBorrow(int noRent, QString fileUrl);
	NetWorker* signReturn(int noRent, QString fileUrl);

	NetWorker* uploadFile(QString fileName);
	QMutex& mtx() { return m_mtx; }

signals:
	void next();
	void update(bool result);
	void upload(bool result);

private:
	QNetworkRequest createRequest(QString suffixUrl, QUrlQuery queries);

private:
	NetWorker(QObject *parent = NULL);
	~NetWorker();
	static NetWorker* m_instance;

	QQueue<NetHost*> m_hosts;

	QNetworkReply* m_netReply;
	Model* m = nullptr;
	QNetworkAccessManager m_netManager;

	QString receivedMsg;

	QMutex m_mtx;
	//QUrlQuery m_queries;

	const QString DOMAIN_NAME = "http://smart.e-koreatech.ac.kr";

};

