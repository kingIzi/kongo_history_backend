#include "request.hpp"

#include <QRegularExpression>
#include <QDebug>

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

//sets the headers required for the GET request and authenticates with dToken
const QNetworkRequest Request::makeGetRequest(const QUrl& url, const QString& idToken) const {

}

//sets the headers required for the POST request and authenticates with dToken
const QNetworkRequest Request::makePostRequest(const QUrl& url, const QString& idToken) const {

}

//sets the headers required for the PUT request and authenticates with dToken
const QNetworkRequest Request::makePutRequest(const QUrl& url, const QString& idToken) const {

}

//sets the headers required for the DELETE request and authenticates with dToken
const QNetworkRequest Request::makeDeleteRequest(const QUrl& url, const QString& idToken) const {

}

//peform network request

//perform a GET request to the server and returns a reply
QNetworkReply* Request::performGet(const QNetworkRequest& request) const {

}

//perform a POST request to the server with body as payload
QNetworkReply* Request::performPost(const QNetworkRequest& request, const QJsonDocument& body) const {

}

//perform a PUT request to the server with body as payload
QNetworkReply* Request::performPut(const QNetworkRequest& request, const QJsonDocument& body) const {

}

//perform a DELETE request to the server and returns a reply
QNetworkReply* Request::performDelete(const QNetworkRequest& request) const {

}

//helpers

//uses query params and a valid path to build a url (endpoint)
const QUrl Request::buildUrl(const QList<std::pair<QString, QString>>& queries, const QString& path) const {

}

//slots

//slot for network reply res
void Request::requestFinished(const QNetworkReply* reply) {

}

void Request::uploadProgressChanged(qint64 bytesReceived, qint64 bytesTotal) {

}

void Request::downloadProgessChanged(qint64 bytesReceived, qint64 bytesTotal) {

}