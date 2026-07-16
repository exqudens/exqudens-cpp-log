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

TEST_F(JsonUtilsUnitTests, test_toMapStringString_1) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::map<std::string, std::string> expected = {};
        expected["id"] = "Abc123!";
        std::cout << LOGGER_ID << " expected.id: '" << expected.at("id") << "'" << std::endl;

        std::map<std::string, std::string> actual = exqudens::log::util::JsonUtils::toMapStringString("{\"id\": \"Abc123!\"}");
        std::cout << LOGGER_ID << " actual.id: '" << actual.at("id") << "'" << std::endl;

        ASSERT_EQ(expected.at("id"), actual.at("id"));

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
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

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
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

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
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

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
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_004) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_005) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_006) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_007) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_008) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

TEST_F(JsonUtilsUnitTests, test_toConfiguration_1_009) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;
        std::optional<std::string> exceptionString = {};

        try {
            exqudens::log::util::JsonUtils::toConfiguration(testInputJson);
        } catch (const std::exception& toConfigurationException) {
            exceptionString = TestUtils::toString(toConfigurationException);
        }

        std::cout << LOGGER_ID << " exceptionString: '" << exceptionString.value_or("") << "'" << std::endl;

        ASSERT_TRUE(exceptionString.has_value());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}

#undef CALL_INFO
