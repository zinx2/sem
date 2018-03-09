#include "networker.h"
#include <QMutexLocker>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "model.h"
//#include "imageresponseprovider.h"

NetWorker* NetWorker::m_instance = nullptr;
NetWorker::NetWorker(QObject *parent) : QObject(parent)
{
	m = Model::instance();
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

void NetWorker::getUserList()
{
	requestPOST(createRequest("/sem/getUserList"),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();

		if (!isSuccess) {
			m_netReply->deleteLater();
			return;
		}

		QList<Employee*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		int no = 1;
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();

			Employee* d = new Employee(); 
			d->setNoUser(obj["sem_user_no"].toInt());
			d->setNameUser(obj["sem_user_name"].toString());
			d->isManager(obj["sem_is_admin"].toBool());
			qDebug() << d->noUser() << "/" << d->nameUser() << "/" << d->manager();
			list.append(d);
		}
		m->setEmployees(list);
		m_netReply->deleteLater();
	});
}

void NetWorker::getPartList()
{

	requestPOST(createRequest("/sem/getPartList"),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();

		if (!isSuccess) {
			m_netReply->deleteLater();
			return;
		}

		QList<Part*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();

			Part* d = new Part();
			d->setNoPart(obj["part_no"].toInt());
			d->setNamePart(obj["part_name"].toString());
			d->isSystem(obj["is_system_part"].toBool());
			qDebug() << d->noPart() << "/" << d->namePart() << "/" << d->system();
			list.append(d);
		}
		m->setParts(list);
		m_netReply->deleteLater();
	});
}

void NetWorker::getDeviceList(int searchType, int now)
{

	/********** SET URL QUERIES **********/
	m_queries.addQueryItem("search_type", QString("%1").arg(searchType));
	m_queries.addQueryItem("now_page", QString("%1").arg(now));

	requestPOST(createRequest("/sem/getDeviceList"),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();

		if (!isSuccess) {
			m_netReply->deleteLater();
			return;
		}
		int totalPage = jsonObj["total_page"].toInt();

		QList<Device*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();

			Device *d = new Device();
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setBarcode(obj["barcode"].toString());
			d->setPrice(obj["get_money"].toString());
			d->setDateTaked(obj["get_date"].toString());
			d->setMemo(obj["memo"].toString());
			d->borrow(obj["is_rented"].toInt());
			qDebug() << d->noDevice() << "/" << d->nameDevice() << d->noAsset() << "/" << d->barcode() << "/" << d->price() << "/" << d->dateTaked() << "/" << d->memo() << "/" << d->borrowed();
			list.append(d);
		}
		m->setDevices(list);
		m_netReply->deleteLater();

	});
}

void NetWorker::getRentList(int now)
{
	/********** SET URL QUERIES **********/
	m_queries.addQueryItem("now_page", QString("%1").arg(now));

	requestPOST(createRequest("/sem/getRentList"),
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();

		if (!isSuccess) {
			m_netReply->deleteLater();
			return;
		}
		int totalPage = jsonObj["total_page"].toInt();

		QList<Rent*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			Rent *d = new Rent();
			d->setNoRent(obj["rent_no"].toInt());
			d->setNameUser(obj["sem_user_name"].toString());
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setDateBorrowed(obj["rent_date"].toString());
			d->setDateReturned(obj["return_date"].toString());
			d->setSignUser(obj["signature"].toString());
			d->complete(obj["is_complete"].toInt());
			d->setNameAdmin(obj["confirm_user_name"].toString());
			d->setSignAdmin(obj["confirm_signature"].toString());
			qDebug() << d->noRent() << "/" << d->nameUser();
			list.append(d);
		}
		m->setRents(list);
		m_netReply->deleteLater();

	});
}