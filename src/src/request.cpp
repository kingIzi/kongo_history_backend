#include "request.hpp"

#include <algorithm>

#include <QRegularExpression>
#include <QDebug>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QVariantMap>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFileInfo>
#include <QFile>
#include <QIODevice>




//init static members

const char* Request::URL_FORMAT_REGEX = "^(https?:\/\/)?[0-9a-z]+\.[-_0-9a-z]+\.[0-9a-z]+$";

//constructors

//construct class initializes all members
Request::Request(const QString& baseUrl, QObject* parent) :
	baseUrl(baseUrl), manager(std::make_unique<QNetworkAccessManager>()), isOperating(false),
	QObject{parent}
{
	try {
		if (this->baseUrl == nullptr)
			throw std::invalid_argument("Error! baseUrl was nullptr");
		else if (!this->baseUrl.contains(QRegularExpression(Request::URL_FORMAT_REGEX)))
			throw std::invalid_argument("Error! baseUrl was did not match regex");
	}
	catch (const std::invalid_argument&  e) {
		qDebug() << "Failed to register member Request::baseUrl" << e.what();
		this->setBaseUrl("");
	}
}

//default destructor
Request::~Request() {

}

//getter & setters

//sets the base url of the requests
void Request::setBaseUrl(const QString& baseUrl) {
	this->baseUrl = baseUrl;
}

//returns the app base url
const QString Request::getBaseUrl() const {
	return this->baseUrl;
}

//resets network manager and points to newManager
void Request::setManager(QNetworkAccessManager* manager) {

}

//returns network manager
QNetworkAccessManager* Request::getManager() const {
	return this->manager.get();
}

//modifies isOperating
void Request::setIsOperating(const bool isOperating) {

}

//returns whether or not a request is being proccessed
const bool Request::getIsOperating() const {
	return this->isOperating;
}

//make network requests

QNetworkReply* Request::makeMultiPartPostRequest(const QUrl& url, const QString& idToken, const QJsonDocument& document) const {
	if (idToken.isEmpty())
		throw std::runtime_error("NO IDTOKEN FOUND TO REQUEST");
	if (document.isEmpty())
		return nullptr;

	auto * multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	const auto parts = this->buildRequestHttpParts(document, multiPart);
	if (parts.isEmpty())
		return nullptr;

	std::for_each(parts.begin(), parts.end(), [multiPart](const QHttpPart & part) { multiPart->append(part); });
	QNetworkRequest request(url);
	const auto headerBearerToken = QString("Bearer %1").arg(idToken);
	request.setRawHeader(QByteArray("Authorization"), headerBearerToken.toUtf8());

	const auto reply = this->manager->post(request, multiPart);
	multiPart->setParent(reply);
	return reply;
}

QNetworkReply* Request::makeMultiPutRequest(const QUrl& url, const QString& idToken, const QJsonDocument& document) const {
	if (idToken.isEmpty())
		throw std::runtime_error("NO IDTOKEN FOUND TO REQUEST");
	if (document.isEmpty())
		return nullptr;

	auto * multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	const auto parts = this->buildRequestHttpParts(document, multiPart);
	if (parts.isEmpty())
		return nullptr;

	std::for_each(parts.begin(), parts.end(), [multiPart](const QHttpPart & part) { multiPart->append(part); });
	QNetworkRequest request(url);
	const auto headerBearerToken = QString("Bearer %1").arg(idToken);
	request.setRawHeader(QByteArray("Authorization"), headerBearerToken.toUtf8());

	const auto reply = this->manager->put(request, multiPart);
	multiPart->setParent(reply);
	return reply;
}

QNetworkReply* Request::makeJsonPostRequest(const QUrl& url, const QString& idToken, const QJsonDocument& document) const {
	
}

QNetworkReply* Request::makeJsonPutRequest(const QUrl& url, const QString& idToken, const QJsonDocument& document) const {

}

QNetworkReply* Request::makeGetRequest(const QUrl& url, const QString& idToken) const {

}

QNetworkReply* Request::makeDeleteRequest(const QUrl& url, const QString& idToken) const {

}

//helpers

//uses query params and a valid path to build a url (endpoint)
const QUrl Request::buildUrl(const QList<QPair<QString, QString>>& queries, const QString& path) const {
	if (this->baseUrl.isEmpty())
		throw std::invalid_argument("Error! base url is empty");

	const auto removeMissingQueryItems = [](const QPair<QString, QString>& value) {
		return value.first != nullptr && !value.first.isEmpty() && value.second != nullptr
		       && !value.second.isEmpty();
	};
	QList<QPair<QString, QString>> queryItems;
	std::copy_if(queries.begin(), queries.end(), std::back_inserter(queryItems), removeMissingQueryItems);

	QUrl endpoint(this->baseUrl);
	endpoint.setPath(path);
	if (!queryItems.isEmpty()) {
		QUrlQuery query;
		query.setQueryItems(queryItems);
		endpoint.setQuery(query);
	}
	return endpoint;
}

const QByteArray Request::buildRawJsonFromDocument(const QJsonDocument& document) const {
	if (document.isEmpty())
		return QByteArray();
	return ((QByteArray) document.toJson()).insert(0, "form-data; ");
}

void Request::appendHttpFilePart(QList<QHttpPart>& parts, const QJsonObject& filesObj, QHttpMultiPart* multiPart) const {
	if (!filesObj.isEmpty()) {
		for (const auto& fileKey : filesObj.keys()) {
			QFileInfo fileInfo(filesObj.value(fileKey).toString());
			if (!fileInfo.isFile())
				throw std::invalid_argument("Error! Files are invalid");

			QVariantMap fileData;
			fileData.insert(fileKey, fileInfo.fileName());
			QHttpPart filePart;
			filePart.setHeader(QNetworkRequest::ContentTypeHeader, QMimeDatabase().mimeTypeForFile(fileInfo.absoluteFilePath()).name());
			filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
			                   this->buildRawJsonFromDocument(QJsonDocument::fromVariant(fileData)));
			auto * file = new QFile(fileInfo.absoluteFilePath());
			if (file->open(QIODevice::ReadOnly))
				filePart.setBodyDevice(file);
			file->setParent(multiPart);
			parts.push_back(filePart);
		}
	}
}

const QList<QHttpPart> Request::buildRequestHttpParts(const QJsonDocument& document, QHttpMultiPart* multiPart) const {
	if (!document.isObject())
		throw std::runtime_error("Error! Request Body must be an object.");

	auto object = document.object();
	QList<QHttpPart> parts; parts.reserve(object.keys().size());
	const auto filesObj = object.value("files").isNull() ? QJsonObject() : object.value("files").toObject();
	if (!filesObj.isEmpty()) {
		try {
			this->appendHttpFilePart(parts, filesObj, multiPart);
		}
		catch (const std::invalid_argument& err) {
			qDebug(err.what());
			return QList<QHttpPart>();
		}
		object.remove("files");
	}
	const auto rawBody = this->buildRawJsonFromDocument(QJsonDocument::fromVariant(object.toVariantMap()));
	QHttpPart part;
	part.setHeader(QNetworkRequest::ContentDispositionHeader, rawBody);
	part.setBody("DOCUMENT TEXT");
	parts.push_back(part);
	return parts;
}

//slots

//slot for network reply res
void Request::requestFinished(const QNetworkReply* reply) {

}

void Request::uploadProgressChanged(qint64 bytesReceived, qint64 bytesTotal) {

}

void Request::downloadProgessChanged(qint64 bytesReceived, qint64 bytesTotal) {

}