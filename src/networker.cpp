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
	connect(this, SIGNAL(next()), this, SLOT(request()));
}
NetWorker::~NetWorker()
{
	//delete m_model;
}

void NetWorker::request()
{
	if (m_hosts.isEmpty()) 
		return;

	NetHost* host = m_hosts.front();
	QNetworkRequest req = createRequest(host->addr(), host->queries());
	qDebug() << "[" << host->type() << "] Called Function: " + req.url().toString();
	qDebug() << "[" << host->type() << "] Called Function: " + req.url().query().toUtf8();
	if (!host->type().compare("post"))
		m_netReply = m_netManager.post(req, req.url().query().toUtf8());
	else if (!host->type().compare("get"))
		m_netReply = m_netManager.get(req);
	else return;

	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
	connect(m_netReply, &QNetworkReply::finished, host->func());
	m_hosts.pop_front();
}

//void NetWorker::requestGET(QNetworkRequest req, FUNC parser)
//{
//	qDebug() << "[**] Called Function: " + req.url().toString();
//	//QNetworkAccessManager m_netManager;
//	m_netReply = m_netManager.get(req);
//	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
//	connect(m_netReply, &QNetworkReply::finished, parser);
//}
//
//void NetWorker::requestPOST(QNetworkRequest req, FUNC parser)
//{
//	qDebug() << "[**] Called Function: " + req.url().toString();
//
//	m_netReply = m_netManager.post(req, req.url().query().toUtf8());
//	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
//	connect(m_netReply, &QNetworkReply::finished, parser);
//}

QNetworkRequest NetWorker::createRequest(QString suffixUrl, QUrlQuery queries)
{
	QUrl url(DOMAIN_NAME + suffixUrl);
	if (!queries.isEmpty())
		url.setQuery(queries);

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");

	queries.clear();
	return request;
}

void NetWorker::httpError(QNetworkReply::NetworkError msg)
{
	qDebug() << "[**] THE ERROR WAS OCCURED. " << msg;
}

void NetWorker::getDemoAll()
{
	/********** SET URL QUERIES **********/

	//requestGET(createRequest("getDemoAll"),
	//	[&]()-> void {
	//	/********** PROCESS SEQUENTIALLY REQUESTS, SO BE DECLARED MUTEX **********/
	//	QMutexLocker locker(&m_mtx);

	//	/********** PARSE BINARY DATA TO JSON **********/
	//	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
	//	QJsonObject jsonObj = jsonDoc.object();
	//	QJsonArray jsonArr = jsonObj["list"].toArray();

	//	/********** MAKE MODEL USING PARSED JSON DATA **********/
	//	foreach(const QJsonValue &value, jsonArr)
	//	{
	//		QJsonObject obj = value.toObject();
	//		QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
	//		qDebug() << data;
	//	}

	//	/********** CLEAR QNetworkReply INSTANCE **********/
	//	m_netReply->deleteLater();
	//});
}
void NetWorker::getDemo(int id)
{
	//requestGET(createRequest("getDemo/" + QString("%1").arg(id)),
	//	[&]()-> void {
	//	QMutexLocker locker(&m_mtx);

	//	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
	//	QJsonObject jsonObj = jsonDoc.object();
	//	QJsonArray jsonArr = jsonObj["list"].toArray();

	//	foreach(const QJsonValue &value, jsonArr)
	//	{
	//		QJsonObject obj = value.toObject();
	//		QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
	//		qDebug() << data;
	//	}

	//});
}
void NetWorker::postDemoAll()
{
	//requestPOST(createRequest("postDemoAll"),
	//	[&]()-> void {
	//	QMutexLocker locker(&m_mtx);

	//	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
	//	QJsonObject jsonObj = jsonDoc.object();
	//	QJsonArray jsonArr = jsonObj["list"].toArray();

	//	foreach(const QJsonValue &value, jsonArr)
	//	{
	//		QJsonObject obj = value.toObject();
	//		QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
	//		qDebug() << data;
	//	}


	//	m_netReply->deleteLater();
	//});
}
void NetWorker::postDemo(int id)
{
	/********** SET URL QUERIES **********/
	//m_queries.addQueryItem("idx", QString("%1").arg(id));

	//requestPOST(createRequest("postDemo"),
	//	[&]()-> void {

	//	/********** PROCESS SEQUENTIALLY REQUESTS **********/
	//	QMutexLocker locker(&m_mtx);

	//	/********** PARSE BINARY DATA TO JSON **********/
	//	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
	//	QJsonObject jsonObj = jsonDoc.object();
	//	QJsonArray jsonArr = jsonObj["list"].toArray();

	//	/********** MAKE MODEL USING PARSED JSON DATA **********/
	//	foreach(const QJsonValue &value, jsonArr)
	//	{
	//		QJsonObject obj = value.toObject();
	//		QString data = QString("%1").arg(obj["id"].toInt()) + ". " + obj["title"].toString();
	//		qDebug() << data;
	//	}

	//	/********** CLEAR QNetworkReply INSTANCE **********/
	//	m_netReply->deleteLater();
	//});
}

NetWorker* NetWorker::getUserList()
{	
	m_hosts.append(new NetHost("post", "/sem/getUserList",
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}

		QList<Employee*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
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
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::getPartList()
{
	m_hosts.append(new NetHost("post", "/sem/getPartList", 
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
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
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::getDeviceList(int noPart, int searchType, int now)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_part_no", QString("%1").arg(noPart));
	queries.addQueryItem("search_type", QString("%1").arg(searchType));
	queries.addQueryItem("now_page", QString("%1").arg(now));

	m_hosts.append(new NetHost("post", "/sem/getDeviceList", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
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
		m_netReply->deleteLater(); emit next();
	}));
	return this;
}
NetWorker* NetWorker::getRentList(int noPart, int now)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_part_no", QString("%1").arg(noPart));
	queries.addQueryItem("now_page", QString("%1").arg(now));
	m_hosts.append(new NetHost("post", "/sem/getRentList", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
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
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::borrowDevice(int barcode, int noUser, QString purpose)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("barcode", QString("%1").arg(barcode));
	queries.addQueryItem("sem_user_no", QString("%1").arg(noUser));
	queries.addQueryItem("purpose", purpose);

	m_hosts.append(new NetHost("post", "/sem/rentDevice", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
		int noRent = jsonObj["rent_no"].toInt();
		m_netReply->deleteLater();
		if (isSuccess && noRent > -1)
			getRentList();

		emit next();
	}));
	return this;
}
NetWorker* NetWorker::signBorrow(int noRent, QString fileUrl)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sig_url", fileUrl);
	queries.addQueryItem("rent_no", QString("%1").arg(noRent));

	m_hosts.append(new NetHost("post", "/sem/setSign", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
		m_netReply->deleteLater();
		getRentList();
	}));
	return this;
}
NetWorker* NetWorker::signReturn(int noRent, QString fileUrl)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sig_url", fileUrl);
	queries.addQueryItem("rent_no", QString("%1").arg(noRent));

	m_hosts.append(new NetHost("post", "/sem/setReturnSign", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
		m_netReply->deleteLater();
		getRentList();
	}));
	return this;
}
NetWorker* NetWorker::returnDevice(int barcode, int noAdmin, bool isInitial)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("barcode", QString("%1").arg(barcode));
	queries.addQueryItem("sem_user_no", QString("%1").arg(noAdmin));
	queries.addQueryItem("is_initial", QString("%1").arg(isInitial));

	m_hosts.append(new NetHost("post", "/sem/returnDevice", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
		int noRent = jsonObj["rent_no"].toInt();

		if (isSuccess && noRent > -1)
			getRentList();

		m_netReply->deleteLater();
	}));
	return this;
}
NetWorker* NetWorker::uploadFile(QString fileName)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("file_name", fileName.toUtf8());

	m_hosts.append(new NetHost("post", "/uploadMissionAnswerFile", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
	}));
	return this;
}