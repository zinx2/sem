#include "networker.h"
#include <QMutexLocker>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
//#include "imageresponseprovider.h"

NetWorker* NetWorker::m_instance = nullptr;
NetWorker::NetWorker(QObject *parent) : QObject(parent)
{
	m_model = Model::getInstance();
}
NetWorker::~NetWorker()
{
	//delete m_model;
}

void NetWorker::requestGET(QNetworkRequest req, std::function<void()> parser)
{
	qDebug() << "[**] Called Function: " + req.url().toString();

	m_netReply = m_netManager.get(req);
	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
	connect(m_netReply, &QNetworkReply::finished, parser);
}

void NetWorker::requestPOST(QNetworkRequest req, std::function<void()> parser)
{
	qDebug() << "[**] Called Function: " + req.url().toString();

	m_netReply = m_netManager.post(req, req.url().query().toUtf8());
	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
	connect(m_netReply, &QNetworkReply::finished, parser);
}

QNetworkRequest NetWorker::createRequest(QString suffixUrl)
{
	QUrl url(DOMAIN_NAME + suffixUrl);
	if (!m_queries.isEmpty())
		url.setQuery(m_queries);

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");

	m_queries.clear();
	return request;
}

void NetWorker::httpError(QNetworkReply::NetworkError msg)
{
	qDebug() << "[**] THE ERROR WAS OCCURED. " << msg;
}

void NetWorker::getDemoAll()
{
	/********** SET URL QUERIES **********/

	requestGET(createRequest("getDemoAll"),
		[&]()-> void {
		/********** PROCESS SEQUENTIALLY REQUESTS, SO BE DECLARED MUTEX **********/
		QMutexLocker locker(&m_mtx);

		/********** PARSE BINARY DATA TO JSON **********/
		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonArr = jsonObj["list"].toArray();

		/********** MAKE MODEL USING PARSED JSON DATA **********/
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
			qDebug() << data;
		}

		/********** CLEAR QNetworkReply INSTANCE **********/
		m_netReply->deleteLater();
	});
}

void NetWorker::getDemo(int id)
{
	requestGET(createRequest("getDemo/" + QString("%1").arg(id)),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonArr = jsonObj["list"].toArray();

		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
			qDebug() << data;
		}

	});
}

void NetWorker::postDemoAll()
{
	requestPOST(createRequest("postDemoAll"),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonArr = jsonObj["list"].toArray();

		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
			qDebug() << data;
		}


		m_netReply->deleteLater();
	});
}
void NetWorker::postDemo(int id)
{
	/********** SET URL QUERIES **********/
	m_queries.addQueryItem("idx", QString("%1").arg(id));

	requestPOST(createRequest("postDemo"),
		[&]()-> void {

		/********** PROCESS SEQUENTIALLY REQUESTS **********/
		QMutexLocker locker(&m_mtx);

		/********** PARSE BINARY DATA TO JSON **********/
		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonArr = jsonObj["list"].toArray();

		/********** MAKE MODEL USING PARSED JSON DATA **********/
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
			qDebug() << data;
		}

		/********** CLEAR QNetworkReply INSTANCE **********/
		m_netReply->deleteLater();
	});
}
