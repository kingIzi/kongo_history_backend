
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "request.hpp"

using namespace testing;

///////////////////////////////////////////////////////////CONSTRUCTOR TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS BEGIN/////////////////////////////////////////////////////////////////////


struct ConstructorTests : ::testing::Test {
    std::unique_ptr<Request> request_ptr = nullptr;
};


//tests for a nullptr string as baseUrl
TEST_F(ConstructorTests, baseUrlInvalidArgumentNull) {
    const QString baseUrl = nullptr;
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for an empty string as baseUrl
TEST_F(ConstructorTests, baseUrlInvalidArgumentEmpty) {
    const QString baseUrl = "";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for one character string as baseUrl
TEST_F(ConstructorTests, baseUrlInvalidArgumentOneCharacter) {
    const QString baseUrl = "{";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for incorrect format string as baseUrl invalid characters in string
TEST_F(ConstructorTests, baseUrlInvalidArgumentIncorrectFormat) {
    const QString baseUrl = "http://\\local/\\host:8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
}

//tests for incorrect protocal name with a space in begining of string
TEST_F(ConstructorTests, baseUrlInvalidArgumentIncorrectProtocalNameHaveSpaceAtBegin) {
    const QString baseUrl = " http://localhost:8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for incorrect protocal name with a space at end of string
TEST_F(ConstructorTests, baseUrlInvalidArgumentIncorrectProtocalNameHaveSpaceAtEnd) {
    const QString baseUrl = "http://localhost:8084 ";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}


//tests for incorrect format endpoints space within name
TEST_F(ConstructorTests, baseUrlInvalidArgumentBaseUrlSpaceBetweenString) {
    const QString baseUrl = "https://lo calhost: 8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for incorrect format endpoints ending with backlash (should reject url)
TEST_F(ConstructorTests, baseUrlInvalidArgumentBaseUrlEndsWithBacklash) {
    const QString baseUrl = "https://localhost:8084/";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_TRUE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for correct format endpoints protocal name is http
TEST_F(ConstructorTests, baseUrlInvalidArgumentBaseUrlProtocalNameIsHttp) {
    const QString baseUrl = "http://localhost:8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_FALSE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for correct format endpoints protocal name is https
TEST_F(ConstructorTests, baseUrlInvalidArgumentBaseUrlProtocalNameIsHttps) {
    const QString baseUrl = "https://localhost:8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_FALSE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}

//tests for incorrect protocal name with a space in middle of string
TEST_F(ConstructorTests, baseUrlInvalidArgumentIncorrectProtocalNameHaveSpaceAtMiddle) {
    const QString baseUrl = "http://local host:8084";
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_FALSE(this->request_ptr->getBaseUrl().isEmpty());
    EXPECT_TRUE(this->request_ptr->getManager());
    EXPECT_FALSE(this->request_ptr->getIsOperating());
}


///////////////////////////////////////////////////////////CONSTRUCTOR TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////CONSTRUCTOR TESTS END//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////BUILD URL TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS BEGIN/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS BEGIN/////////////////////////////////////////////////////////////////////

struct BuildUrlTests : ::testing::Test {
    std::unique_ptr<Request> request_ptr = nullptr;
};

TEST_F(BuildUrlTests, emptyList) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {};
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_FALSE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, invalidBaseUrl) {
    const QString baseUrl = "http://localhost:8084 ";
    const QString path = "/test/path";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {};
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_THROW(this->request_ptr->buildUrl(queries, path), std::invalid_argument);
}

TEST_F(BuildUrlTests, queriesMissingKeysAtFirst) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {
        QPair("", "value"),
                  QPair("key", "value")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_TRUE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, queriesMissingKeysAtEnd) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value&data=sample";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {
        QPair("key", "value"),
                  QPair("data", "sample"),
                  QPair("key", "")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_TRUE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, queriesMissingKeysAtMiddle) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value&home=tanzania&sample=data";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {
        QPair("key", "value"),
                  QPair("data", ""),
                  QPair("home", "tanzania"),
                  QPair("sample", "data")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_TRUE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, queriesCorrectFormat) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {
        QPair("key", "value")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_TRUE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, queriesInvalidQueries) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path";
    QList<QPair<QString, QString>> queries = (QList<QPair<QString, QString>>) {
        QPair("key", ""),
                  QPair("", ""),
                  QPair("", "value")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_FALSE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

///////////////////////////////////////////////////////////BUILD URL TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS END//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////BUILD URL TESTS END//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////MAKE REQUESTS START//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////MAKE REQUESTS START//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////MAKE REQUESTS START//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////MAKE REQUESTS START//////////////////////////////////////////////////////////////////////

struct MakeRequestTests : ::testing::Test {
    const QString baseUrl = "https://postman-echo.com";
    std::unique_ptr<Request> request_ptr = std::make_unique<Request>(this->baseUrl);
};


TEST_F(MakeRequestTests,getRawjsonDocumentEmpty){
    QJsonDocument document;
    const auto raw = this->request_ptr->getRawJsonFromDocument(document);
    EXPECT_TRUE(raw.isEmpty());
}

TEST_F(MakeRequestTests,getRawjsonDocumentMissingValue){
    QJsonObject object; 
    object.insert("key","");
    QJsonDocument document(object);
    const auto raw = this->request_ptr->getRawJsonFromDocument(document);
    qDebug() << raw;
    EXPECT_TRUE(QString(raw.toStdString().c_str()).startsWith("form-data; "));
    EXPECT_TRUE(!raw.isEmpty());
}

TEST_F(MakeRequestTests,multipartPostEmptyIdToken){
    const auto path = "/post";
    const QString idToken = "";
    QJsonObject object; 
    object.insert("key","value");
    const QJsonDocument document(object);

    const auto url = this->request_ptr->buildUrl({},path);
    EXPECT_THROW(this->makeMultiPartPostRequest(url,idToken,document));    
}

/*TEST_F(MakeRequestTests,multipartPostEmptyDocument){
    const auto path = "/post";
    const QString idToken = "eyJ0eXAiOiJKV1QiLCJraWQiOiJyaWpwdHZxYnlrZXF4c2F0IiwiYWxnIjoiUlMyNTYifQ.eyJpc3MiOiJodHRwczovL2F1LWNvbGxlY3QuY29tIiwiYXVkIjoiQVVfQ09MTEVDVCIsImV4cCI6MTY3NzY3OTQ1OSwianRpIjoiMl80VnctWFY0N0I2bzNCOFZBYjFMZyIsImlhdCI6MTY3NzY3NzY1OSwibmJmIjoxNjc3Njc3NTM5LCJzdWIiOiJhZG1pbjEyMzQiLCJzY29wZSI6bnVsbCwiYXBwcyI6W119.Hji_YpA6FXpMT75hqB4oe_tKhlwyx_rA6PJ2ermpAIvUf8gDG1YE-nB3Wuotk8K2ptkA4GjmSBb5QH4Zx9dxgXf-ER3BEiJOl9fAN2KK9XBEEefuFKHvTmyr4GhYJytwMABcojdVTuUricgdrMbKRdm9WnenV5PXwu_Sv0ezMjN5mwHFxECzNf22Qjlv-9rty8WiPgNoZ7e_6dMJcoVO1f6URYWzE74PbY_t2V1_2B77G06JhlK-KV_rGQnzZ0uPbOi7HnkT2Zs2b1w12yrYQQlUU0cTfFD6PKeuSPpkYSTwioRNiGW3mfFnPiIA3_A20r7KnGoFgXmkfdGicyLCOg";
    QJsonObject object; 
    object.insert("key","");
    const QJsonDocument document(object);
    const auto url = this->request_ptr->buildUrl({},path);
    EXPECT_FALSE(this->makeMultiPartPostRequest(url,idToken,document));
}
*/

