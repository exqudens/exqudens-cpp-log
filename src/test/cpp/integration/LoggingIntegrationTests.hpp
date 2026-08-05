#pragma once

#include <string>
#include <optional>
#include <filesystem>

#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/log/api/Logging.hpp"

class LoggingIntegrationTests: public testing::Test {

    protected:

        inline static const char* LOGGER_ID = "LoggingIntegrationTests";

    private:

        inline static std::optional<std::string> defaultWorkingDirectory = {};

    public:

        static void SetUpTestSuite() {
            defaultWorkingDirectory = std::filesystem::current_path().generic_string();
        }

        static void TearDownTestSuite() {
            std::filesystem::current_path(defaultWorkingDirectory.value());
        }

    protected:

        void SetUp() override {
            std::string currentTestGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string currentTestCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::string currentTestOutputDir = TestUtils::getTestOutputDir(currentTestGroup, currentTestCase).value();
            if (std::filesystem::exists(currentTestOutputDir)) {
                std::filesystem::remove_all(currentTestOutputDir);
            }
            std::filesystem::create_directories(currentTestOutputDir);
            std::filesystem::current_path(currentTestOutputDir);
        }

        void TearDown() override {
            std::filesystem::current_path(defaultWorkingDirectory.value());
        }

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

        std::string loggingConfigType = exqudens::log::api::Logging::configure(testInputJson);
        EXQUDENS_LOG(LOGGER_ID, 6) << "loggingConfigType: '" << loggingConfigType << "'";

        ASSERT_TRUE(exqudens::log::api::Logging::isConfigured());

        std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}
