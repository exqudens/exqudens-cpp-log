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
#include "exqudens/log/util/FileHandlerUtils.hpp"

namespace exqudens::log::util {

    class FileHandlerUtilsUnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.log.util.FileHandlerUtilsUnitTests";

    };

    TEST_F(FileHandlerUtilsUnitTests, test_1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::string currentFile = (testInputDir / "log.txt").generic_string();
            std::cout << LOGGER_ID << " currentFile: " << '"' << currentFile << '"' << std::endl;

            size_t maxSize = 20;
            std::cout << LOGGER_ID << " maxSize: " << '"' << maxSize << '"' << std::endl;

            std::string expected = currentFile;
            std::cout << LOGGER_ID << " expected: " << '"' << expected << '"' << std::endl;

            std::string actual = FileHandlerUtils::getNextFileName(currentFile, maxSize);
            std::cout << LOGGER_ID << " actual: " << '"' << actual << '"' << std::endl;

            ASSERT_EQ(expected, actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(FileHandlerUtilsUnitTests, test_2) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::string currentFile = (testInputDir / "log.txt").generic_string();
            std::cout << LOGGER_ID << " currentFile: " << '"' << currentFile << '"' << std::endl;

            size_t maxSize = 20;
            std::cout << LOGGER_ID << " maxSize: " << '"' << maxSize << '"' << std::endl;

            std::string expected = currentFile;
            std::cout << LOGGER_ID << " expected: " << '"' << expected << '"' << std::endl;

            std::string actual = FileHandlerUtils::getNextFileName(currentFile, maxSize);
            std::cout << LOGGER_ID << " actual: " << '"' << actual << '"' << std::endl;

            ASSERT_EQ(expected, actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(FileHandlerUtilsUnitTests, test_3) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::string currentFile = (testInputDir / "log.txt").generic_string();
            std::cout << LOGGER_ID << " currentFile: " << '"' << currentFile << '"' << std::endl;

            size_t maxSize = 20;
            std::cout << LOGGER_ID << " maxSize: " << '"' << maxSize << '"' << std::endl;

            std::string expected = (testInputDir / "log-1.txt").generic_string();
            std::cout << LOGGER_ID << " expected: " << '"' << expected << '"' << std::endl;

            std::string actual = FileHandlerUtils::getNextFileName(currentFile, maxSize);
            std::cout << LOGGER_ID << " actual: " << '"' << actual << '"' << std::endl;

            ASSERT_EQ(expected, actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(FileHandlerUtilsUnitTests, test_4) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::string currentFile = (testInputDir / "log.txt").generic_string();
            std::cout << LOGGER_ID << " currentFile: " << '"' << currentFile << '"' << std::endl;

            size_t maxSize = 20;
            std::cout << LOGGER_ID << " maxSize: " << '"' << maxSize << '"' << std::endl;

            std::string expected = (testInputDir / "log-1.txt").generic_string();
            std::cout << LOGGER_ID << " expected: " << '"' << expected << '"' << std::endl;

            std::string actual = FileHandlerUtils::getNextFileName(currentFile, maxSize);
            std::cout << LOGGER_ID << " actual: " << '"' << actual << '"' << std::endl;

            ASSERT_EQ(expected, actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(FileHandlerUtilsUnitTests, test_5) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::filesystem::path testInputDir(TestUtils::getTestInputDir(testGroup, testCase));
            std::cout << LOGGER_ID << " testInputDir: " << '"' << testInputDir.generic_string() << '"' << std::endl;

            std::string currentFile = (testInputDir / "log.txt").generic_string();
            std::cout << LOGGER_ID << " currentFile: " << '"' << currentFile << '"' << std::endl;

            size_t maxSize = 20;
            std::cout << LOGGER_ID << " maxSize: " << '"' << maxSize << '"' << std::endl;

            std::string expected = (testInputDir / "log-2.txt").generic_string();
            std::cout << LOGGER_ID << " expected: " << '"' << expected << '"' << std::endl;

            std::string actual = FileHandlerUtils::getNextFileName(currentFile, maxSize);
            std::cout << LOGGER_ID << " actual: " << '"' << actual << '"' << std::endl;

            ASSERT_EQ(expected, actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}
