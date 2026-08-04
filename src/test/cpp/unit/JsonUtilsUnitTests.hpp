#pragma once

#include <optional>

#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/log/util/JsonUtils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

class JsonUtilsUnitTests: public testing::Test {

    protected:

        inline static const char* LOGGER_ID = "JsonUtilsUnitTests";

};

TEST_F(JsonUtilsUnitTests, test_getSchema_1) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string jsonString = exqudens::log::util::JsonUtils::getConfigurationSchema();
        exqudens::log::util::json::Value jsonValue = exqudens::log::util::json::Parser(jsonString).parse();
        std::string actualErrorMessage = {};
        bool actual = exqudens::log::util::json::Schema::validate(jsonValue, actualErrorMessage);
        std::cout << LOGGER_ID << " actual: " << actual << std::endl;
        std::cout << LOGGER_ID << " actualErrorMessage: '" << actualErrorMessage << "'" << std::endl;

        ASSERT_TRUE(actual);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_0_000) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        exqudens::log::model::Configuration actual = exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        std::cout << LOGGER_ID << " actual.loggers.root.level: " << actual.loggers.at("root").level << std::endl;
        std::cout << LOGGER_ID << " actual.loggers.root.handlers: " << TestUtils::toString(actual.loggers.at("root").handlers) << std::endl;

        std::cout << LOGGER_ID << " actual.loggers.abc.level: " << actual.loggers.at("abc").level << std::endl;
        std::cout << LOGGER_ID << " actual.loggers.abc.handlers: " << TestUtils::toString(actual.loggers.at("abc").handlers) << std::endl;

        ASSERT_EQ(actual.loggers.at("root").level, actual.loggers.at("abc").level);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_0_001) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        exqudens::log::model::Configuration actual = exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        std::cout << LOGGER_ID << " actual.loggers.root.level: " << actual.loggers.at("root").level << std::endl;
        std::cout << LOGGER_ID << " actual.loggers.root.handlers: " << TestUtils::toString(actual.loggers.at("root").handlers) << std::endl;

        std::cout << LOGGER_ID << " actual.loggers.abc.level: " << actual.loggers.at("abc").level << std::endl;
        std::cout << LOGGER_ID << " actual.loggers.abc.handlers: " << TestUtils::toString(actual.loggers.at("abc").handlers) << std::endl;

        ASSERT_EQ(actual.loggers.at("root").handlers, actual.loggers.at("abc").handlers);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_000) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("Missing required field 'formatters'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_001) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("Missing required field 'handlers'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_002) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("Missing required field 'loggers'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_003) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("Unallowed field 'abc'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_000) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_001) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> Object size below 'minProperties' constraint: 1"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_002) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_003) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> Missing required field 'format'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_004) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> [format] -> Expected 'string'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_005) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> Unallowed field 'abc'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_006) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> [parameters] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_007) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> [parameters] -> Object size below 'minProperties' constraint: 1"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_008) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[formatters] -> [formatter] -> [parameters] -> Unallowed field 'abc'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_2_009) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("___"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_3_000) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[handlers] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_000) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_001) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_002) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> [level] -> Expected 'integer'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_003) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> Missing required field 'root'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_004) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> Missing required field 'level'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_005) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> Missing required field 'handlers'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_006) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> [handlers] -> Array size below 'minItems' constraint: 1"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_007) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [root] -> [handlers] -> [0] -> Expected 'string'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_008) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [abc] -> Expected 'object'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_009) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [abc] -> [level] -> Value exceeds 'maximum' constraint: 6"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_010) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [abc] -> [handlers] -> [0] -> Expected 'string'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_4_011) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        bool valid = false;
        std::string errorMessage = {};
        exqudens::log::util::JsonUtils::toConfiguration(testInputJson, valid, errorMessage);
        std::cout << LOGGER_ID << " valid: " << valid << std::endl;
        std::cout << LOGGER_ID << " errorMessage: '" << errorMessage << "'" << std::endl;

        ASSERT_FALSE(valid);
        ASSERT_EQ(std::string("[loggers] -> [abc] -> [handlers] -> [0] -> Expected 'string'"), errorMessage);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

#undef CALL_INFO
