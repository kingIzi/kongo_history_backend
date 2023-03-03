#pragma once

#include <memory>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QJsonDocument>
#include <QList>
#include <QUrl>
#include <QObject>
#include <QPair>
#include <QByteArray>
#include <QHttpPart>


#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


class Request : public QObject {
	Q_OBJECT
private:
	QString baseUrl;
	std::unique_ptr<QNetworkAccessManager> manager;
	bool isOperating;
	static const char* URL_FORMAT_REGEX;
private:
	const QList<QHttpPart> buildRequestHttpParts(const QJsonDocument& document) const;
public:
	//constructor destructor
	explicit Request(const QString& baseUrl, QObject* parent = nullptr);
	~Request();

	//Getters & Setters
	void setManager(QNetworkAccessManager* manager);
	QNetworkAccessManager* getManager() const;
	void setBaseUrl(const QString& baseUrl);
	const QString getBaseUrl() const;
	void setIsOperating(const bool isOperating);
	const bool getIsOperating() const;

	//make request

	QNetworkReply* makeMultiPartPostRequest(const QUrl& url, const QString& idToken,
	                                        const QJsonDocument& document) const;

	QNetworkReply* makeMultiPutPostRequest(const QUrl& url, const QString& idToken,
	                                       const QJsonDocument& document) const;

	QNetworkReply* makeJsonPostRequest(const QUrl& url, const QString& idToken,
	                                   const QJsonDocument& document) const;

	QNetworkReply* makeJsonPutRequest(const QUrl& url, const QString& idToken,
	                                  const QJsonDocument& document) const;
	QNetworkReply* makeGetRequest(const QUrl& url, const QString& idToken) const;
	QNetworkReply* makeDeleteRequest(const QUrl& url, const QString& idToken) const;

	//helper
	const QUrl buildUrl(const QList<QPair<QString, QString>>& queries, const QString& path) const;
	const QByteArray buildRawJsonFromDocument(const QJsonDocument& document) const;
signals:
	void response(const QJsonDocument httpDataResponse);
public slots:
	void requestFinished(const QNetworkReply* reply); //emits Request::response(QJsonDocument)
	void uploadProgressChanged(qint64 bytesReceived, qint64 bytesTotal);
	void downloadProgessChanged(qint64 bytesReceived, qint64 bytesTotal);
};