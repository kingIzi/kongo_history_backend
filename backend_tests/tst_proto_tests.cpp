
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
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {};
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_FALSE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, invalidBaseUrl) {
    const QString baseUrl = "http://localhost:8084 ";
    const QString path = "/test/path";
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {};
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_THROW(this->request_ptr->buildUrl(queries, path), std::invalid_argument);
}

TEST_F(BuildUrlTests, queriesMissingKeysAtFirst) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value";
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {
        std::make_pair("", "value"),
            std::make_pair("key", "value")
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
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {
        std::make_pair("key", "value"),
            std::make_pair("data", "sample"),
            std::make_pair("key", "")
    };
    this->request_ptr = std::make_unique<Request>(baseUrl);
    EXPECT_NO_THROW(this->request_ptr->buildUrl(queries, path));
    EXPECT_EQ(this->request_ptr->buildUrl(queries, path).toString(), expected);
    EXPECT_TRUE(this->request_ptr->buildUrl(queries, path).hasQuery());
}

TEST_F(BuildUrlTests, queriesMissingKeysAtMiddle) {
    const QString baseUrl = "http://localhost:8084";
    const QString path = "/test/path";
    const QString expected = "http://localhost:8084/test/path?key=value&sample=data&home=tanzania";
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {
        std::make_pair("key", "value"),
            std::make_pair("data", ""),
            std::make_pair("home", "tanzania"),
            std::make_pair("sample", "data")
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
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {
        std::make_pair("key", "value")
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
    QList<std::pair<QString, QString>> queries = (QList<std::pair<QString, QString>>) {
        std::make_pair("key", ""),
        std::make_pair("", ""),
        std::make_pair("", "value"),
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
