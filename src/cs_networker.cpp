#include "cs_networker.h"
#include <QMutexLocker>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "cs_model.h"
#include <QHttpMultiPart>
#include <QDir>
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
	if (!host->type().compare("post"))
		m_netReply = m_netManager.post(req, req.url().query().toUtf8());
	else if (!host->type().compare("get"))
		m_netReply = m_netManager.get(req);
	else return;

	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
	connect(m_netReply, &QNetworkReply::finished, host->func());
	m_hosts.pop_front();
}

void NetWorker::requestFile()
{
	if (m_hosts.isEmpty())
		return;

	NetHost* host = m_hosts.front();
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	QHttpPart textPart;
	QString fileName = QDir::currentPath() + "/tmp.jpg";
	textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file_name\""));
	textPart.setBody("tmp.jpg");
	QHttpPart imagePart;
	imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg")); /*jpeg*/

	imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\""));
	QFile *file = new QFile(host->file());
	file->open(QIODevice::ReadOnly);
	imagePart.setBodyDevice(file);
	file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

	multiPart->append(textPart);
	multiPart->append(imagePart);

	QUrl url(DOMAIN_NAME + host->addr());
	if (!host->queries().isEmpty())
		url.setQuery(host->queries());

	QNetworkRequest req(url);

	qDebug() << "[" << host->type() << "] Called Function: " + req.url().toString();
	m_netReply = m_netManager.post(req, multiPart);
	multiPart->setParent(m_netReply);

	connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
	//connect(m_netReply, &QNetworkReply::finished, host->func());
	connect(m_netReply, SIGNAL(finished()), this, SLOT(done()));
	connect(m_netReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
	m_hosts.pop_front();
}
void NetWorker::done()
{
	qDebug() << "done";
	QMutexLocker locker(&m_mtx);

	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
	QJsonObject jsonObj = jsonDoc.object();
	bool isSuccess = jsonObj["is_success"].toBool();
	QString url = jsonObj["file_url"].toString();
	QString name = jsonObj["file_name"].toString();

	Notificator * nott = new Notificator(isSuccess, jsonObj["error_message"].toString(), url, name, Notificator::File);
	nott->showDialog(true);
	m->setNotificator(nott);
}
void NetWorker::progress(qint64 a, qint64 b)
{
	qDebug() << a << "/" << b;
}
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
			d->isManager(obj["sem_is_admin"].toInt());
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
	queries.addQueryItem("now_page", QString("%1").arg(m->pageNumber()));
	qDebug() << m->pageNumber();

	m_hosts.append(new NetHost("post", "/sem/getDeviceList", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		qDebug() << m_netReply->readAll();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m_netReply->deleteLater();
			emit next(); return;
		}
		int totalPage = jsonObj["total_page"].toInt();

		QList<Device*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		int count = 0;
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();

			Device *d = new Device();
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setBarcode(obj["barcode"].toString());
			d->setPrice(obj["get_money"].toInt());
			d->setDateTaked(obj["get_date"].toString());
			d->setMemo(obj["memo"].toString());
			d->borrow(obj["is_rented"].toInt());
			qDebug() << d->noDevice() << "/" << d->nameDevice() << d->noAsset() << "/" << d->barcode() << "/" << d->price() << "/" << d->dateTaked() << "/" << d->memo() << "/" << d->borrowed();
			list.append(d);
			count++;
		}
		m->setCountTotalDevice(totalPage);
		m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
		//m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList, false));
		//m->setPageNumber((m->countCurrentDevice() / COUNT_PAGE) + 1);

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
	queries.addQueryItem("now_page", QString("%1").arg(m->pageNumber()));

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
		int count = 0;
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
			count++;
		}
		m->setCountTotalDevice(totalPage);
		m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
		m->setRents(list);
		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::borrowDevice(QString barcode, int noUser, QString purpose, QString imgPath)
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

		qDebug() << QString(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m_netReply->deleteLater();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::MNGModified));

		//qDebug() << jsonObj["error_message"].toString();
		//if (!isSuccess) {
		//	m_netReply->deleteLater();
		//	emit update(false); return;
		//}
		//int noRent = jsonObj["rent_no"].toInt();
		//m_netReply->deleteLater();
		//if (isSuccess && noRent > -1)
		//{
		//	signBorrow(noRent, QDir::currentPath() + "/tmp.png")->request();
		//}
		//emit update(true);
	}));
	return this;
}
NetWorker* NetWorker::addDevice(int noPart, QString nameDevice, QString noAsset, QString barcode, QString price, QString date, QString memo)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("part_no", QString("%1").arg(noPart));
	queries.addQueryItem("device_name", nameDevice);
	queries.addQueryItem("asset_no", noAsset);
	queries.addQueryItem("barcode", barcode);
	queries.addQueryItem("get_money", price);
	queries.addQueryItem("get_date", date);
	queries.addQueryItem("memo", memo);

	m_hosts.append(new NetHost("post", "/sem/setDevice", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIModified));
		m_netReply->deleteLater();

		if ((m->countCurrentDevice() + 1) % COUNT_PAGE == 1)
		{
			m->setPageNumber(m->pageNumber() + 1);
		}
	}));
	return this;
}
NetWorker* NetWorker::editDevice(int noDevice, int noPart, QString nameDevice, QString noAsset, QString barcode, QString price, QString date, QString memo)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));
	queries.addQueryItem("part_no", QString("%1").arg(noPart));
	queries.addQueryItem("device_name", nameDevice);
	queries.addQueryItem("asset_no", noAsset);
	queries.addQueryItem("barcode", barcode);
	queries.addQueryItem("get_money", price);
	queries.addQueryItem("get_date", date);
	queries.addQueryItem("memo", memo);

	m_hosts.append(new NetHost("post", "/sem/updateDevice", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIModified));
		m_netReply->deleteLater();
		if (!isSuccess) return;


	}));
	return this;
}
NetWorker* NetWorker::removeDevice(int noDevice)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));

	m_hosts.append(new NetHost("post", "/sem/deleteDevice", queries,
		[=]()-> void {
		QMutexLocker locker(&m_mtx);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIModified));
		m_netReply->deleteLater();
		if ((m->countCurrentDevice() - 1) % COUNT_PAGE == 0)
		{
			if (m->pageNumber() > 1)
				m->setPageNumber(m->pageNumber() - 1);
		}
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
			emit upload(false); return;
		}
		m_netReply->deleteLater();
		getRentList();

		//emit upload(true);
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
NetWorker* NetWorker::returnDevice(QString barcode, int noAdmin, int noDevice, bool isInitial)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("barcode", barcode);
	queries.addQueryItem("confirm_user_no", QString("%1").arg(noAdmin));
	queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));
	queries.addQueryItem("is_initial", QString("%1").arg(isInitial));

	m_hosts.append(new NetHost("post", "/sem/returnDevice", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::MNGModified));
		m_netReply->deleteLater();
	}));
	return this;
}
NetWorker* NetWorker::uploadFile(QString fileName)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("file_name", /*fileName.toUtf8()*/"tmp.jpg");

	m_hosts.append(new NetHost("post", "/uploadMissionAnswerFile", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		QString url = jsonObj["file_url"].toString();
		QString name = jsonObj["file_name"].toString();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), url, name, Notificator::File));

	}, fileName));
	return this;
}
NetWorker* NetWorker::expire(int noUser)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_user_no", QString("%1").arg(noUser));

	m_hosts.append(new NetHost("post", "/sem/deleteUser", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());

		qDebug() << QString(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::EMPList));
	}));
	return this;
}

NetWorker* NetWorker::searchDeviceBorrowed(int barcode)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("barcode", QString("%1").arg(barcode));

	m_hosts.append(new NetHost("post", "/sem/getDeviceInfo", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (isSuccess)
		{
			Device *d = new Device();
			d->setNoPart(jsonObj["sem_part_no"].toInt());
			d->setNamePart(jsonObj["sem_part_name"].toString());
			d->setNameDevice(jsonObj["device_name"].toString());
			d->setNoAsset(jsonObj["asset_no"].toString());
			d->setBarcode(jsonObj["barcode"].toString());
			d->setPrice(jsonObj["get_money"].toInt());
			d->setDateTaked(jsonObj["get_date"].toString());
			d->setMemo(jsonObj["memo"].toString());
			d->borrow(jsonObj["is_rented"].toInt());
			m->setSearchedDevice(d);
			qDebug() << d->namePart() << "/" << d->nameDevice() << "/" << d->noAsset() << "/" << d->price() << "/" << d->borrowed();
		}
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIBorrowedSearch, false));
		m_netReply->deleteLater();
	}));
	return this;
}

NetWorker* NetWorker::searchDeviceReturned(int barcode)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("barcode", QString("%1").arg(barcode));

	m_hosts.append(new NetHost("post", "/sem/getDeviceInfo", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (isSuccess)
		{
			Device *d = new Device();
			d->setNoPart(jsonObj["sem_part_no"].toInt());
			d->setNamePart(jsonObj["sem_part_name"].toString());
			d->setNameDevice(jsonObj["device_name"].toString());
			d->setNoAsset(jsonObj["asset_no"].toString());
			d->setBarcode(jsonObj["barcode"].toString());
			d->setPrice(jsonObj["get_money"].toInt());
			d->setDateTaked(jsonObj["get_date"].toString());
			d->setMemo(jsonObj["memo"].toString());
			d->borrow(jsonObj["is_rented"].toInt());
			m->setSearchedDevice(d);
			qDebug() << d->namePart() << "/" << d->nameDevice() << "/" << d->noAsset() << "/" << d->price() << "/" << d->borrowed();
		}
		m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIReturnedSearch, false));
		m_netReply->deleteLater();
	}));
	return this;
}