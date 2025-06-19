#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/Log.hpp"

namespace exqudens {

    class LogIntegrationTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.LogIntegrationTests";

    };

    TEST_F(LogIntegrationTests, test_1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::filesystem::path testOutputDir(TestUtils::getTestOutputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testOutputDir: " << '"' << testOutputDir.generic_string() << '"' << std::endl;

            if (std::filesystem::exists(testOutputDir)) {
                std::filesystem::remove_all(testOutputDir);
            }
            std::filesystem::create_directories(testOutputDir);

            std::string loggingFile = (testOutputDir / "log" / "log.txt").generic_string();
            size_t loggingFileSize = 300;
            std::map<std::string, unsigned short> loggerIdLevelMap = {
                {"test.logger.1", 0}
            };
            std::string loggingConfig = exqudens::Log::configure(loggingFile, loggingFileSize, loggerIdLevelMap);
            std::cout << LOGGER_ID << " loggingConfig: " << '"' << loggingConfig << '"' << std::endl;

            EXQUDENS_LOG_INFO("test.logger.1") << "Abc: 001";
            EXQUDENS_LOG_INFO("test.logger.1") << "Abc: 002";
            EXQUDENS_LOG_INFO("test.logger.1") << "Abc: 003";
            EXQUDENS_LOG_INFO("test.logger.1") << "Abc: 004";

            Log::reset();

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}
