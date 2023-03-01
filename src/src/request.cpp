#include "request.hpp"

#include <algorithm>

#include <QRegularExpression>
#include <QDebug>
#include <QUrlQuery>

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

}

QNetworkReply* Request::makeMultiPutPostRequest(const QUrl& url, const QString& idToken, const QJsonDocument& document) const {
	
}

QNetworkReply* Request::makeJsonPostRequest(const QUrl& url, const QString& idToken,const QJsonDocument& document) const{

}

QNetworkReply* Request::makeJsonPutRequest(const QUrl& url, const QString& idToken,const QJsonDocument& document) const{

}

QNetworkReply* Request::makeGetRequest(const QUrl& url,const QString& idToken) const{

}

QNetworkReply* Request::makeDeleteRequest(const QUrl& url,const QString& idToken) const{
	
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

const QByteArray Request::getRawJsonFromDocument(const QJsonDocument& document) const {
	if (document.isEmpty())
		return QByteArray();
	return ((QByteArray) document.toJson()).insert(0,"form-data; ");
}

//slots

//slot for network reply res
void Request::requestFinished(const QNetworkReply* reply) {

}

void Request::uploadProgressChanged(qint64 bytesReceived, qint64 bytesTotal) {

}

void Request::downloadProgessChanged(qint64 bytesReceived, qint64 bytesTotal) {

}