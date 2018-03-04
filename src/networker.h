#pragma once

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QUrlQuery>
#include "model.h"
#include <QImage>

class NetWorker : public QObject
{
	Q_OBJECT
public:
	static NetWorker* getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new NetWorker();
		return m_instance;
	}

	void requestGET(QNetworkRequest req, std::function<void()> parser);
	void requestPOST(QNetworkRequest req, std::function<void()> parser);

	public slots:
	void httpError(QNetworkReply::NetworkError msg);

	/************* API CALL METHODS ****************/
	void getDemoAll();
	void getDemo(int id);
	void postDemoAll();
	void postDemo(int id);

	void getUserList();
	void getPartList();
	void getDeviceList(int searchType = 0, int now = 1);

private:
	QNetworkRequest createRequest(QString suffixUrl);

private:
	NetWorker(QObject *parent = NULL);
	~NetWorker();

	static NetWorker* m_instance;
	QNetworkReply* m_netReply;
	Model* m = nullptr;
	QNetworkAccessManager m_netManager;

	QString receivedMsg;

	QMutex m_mtx;
	QUrlQuery m_queries;

	const QString DOMAIN_NAME = "http://smart.e-koreatech.ac.kr";
};

