#pragma once

#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/log/api/Logging.hpp"

class LoggingIntegrationTests: public testing::Test {

    protected:

        inline static const char* LOGGER_ID = "LoggingIntegrationTests";

};

TEST_F(LoggingIntegrationTests, test_1) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

        ASSERT_FALSE(exqudens::log::api::Logging::isConfigured());

        std::string testInputDir = TestUtils::getTestInputDir(testGroup, testCase).value();
        std::string testInputJsonFile = std::filesystem::path(testInputDir).append("value.json").generic_string();
        std::string testInputJson = TestUtils::readFileString(testInputJsonFile);
        std::cout << LOGGER_ID << " testInputJson: '" << testInputJson << "'" << std::endl;

        //exqudens::log::api::Logging::configure(testInputJson);

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}
