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

class Request : public QObject{
	Q_OBJECT
private:
	QString baseUrl;
	std::unique_ptr<QNetworkAccessManager> manager;
	bool isOperating;
	static const char* URL_FORMAT_REGEX;
public:
	//constructor destructor
	explicit Request(const QString& baseUrl,QObject* parent = nullptr);
	~Request();

	//Getters & Setters
	void setManager(QNetworkAccessManager* manager);
	QNetworkAccessManager* getManager() const;
	void setBaseUrl(const QString& baseUrl);
	const QString getBaseUrl() const;
	void setIsOperating(const bool isOperating);
	const bool getIsOperating() const;

	//make request
	const QNetworkRequest makeGetRequest(const QUrl& url,const QString& idToken) const;
	const QNetworkRequest makePostRequest(const QUrl& url,const QString& idToken) const;
	const QNetworkRequest makePutRequest(const QUrl& url,const QString& idToken) const;
	const QNetworkRequest makeDeleteRequest(const QUrl& url,const QString& idToken) const;

	//peform request
	QNetworkReply* performGet(const QNetworkRequest& request) const;
	QNetworkReply* performPost(const QNetworkRequest& request,const QJsonDocument& body) const;
	QNetworkReply* performPut(const QNetworkRequest& request,const QJsonDocument& body) const;
	QNetworkReply* performDelete(const QNetworkRequest& request) const;

	//helper
	const QUrl buildUrl(const QList<std::pair<QString,QString>>& queries,const QString& path) const;
signals:
	void response(const QJsonDocument httpDataResponse); 
public slots:
	void requestFinished(const QNetworkReply* reply); //emits Request::response(QJsonDocument)
	void uploadProgressChanged(qint64 bytesReceived,qint64 bytesTotal);
	void downloadProgessChanged(qint64 bytesReceived,qint64 bytesTotal);
};