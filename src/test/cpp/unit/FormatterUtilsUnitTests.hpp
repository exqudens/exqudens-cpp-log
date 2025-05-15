#pragma once

#include <cstddef>
#include <string>
#include <any>
#include <memory>
#include <optional>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestUtils.hpp"

#include "exqudens/log/util/FormatterUtils.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    class FormatterUtilsUnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.FormatterUtilsUnitTests";

    };

    /*!
    * Test functions:
    * - splitFormat
    */
    TEST_F(FormatterUtilsUnitTests, test_1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::vector<std::string> expected = {};
            std::string format = {};
            std::vector<std::string> actual = {};

            // case-1
            expected = {
                " abc 123 "
            };
            std::cout << LOGGER_ID << " expected: " << TestUtils::toString(expected) << std::endl;

            format = TestUtils::join(expected);
            std::cout << LOGGER_ID << " format: '" << format << "'" << std::endl;

            actual = exqudens::log::util::FormatterUtils::splitFormat(format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            std::cout << LOGGER_ID << " actual: " << TestUtils::toString(actual) << std::endl;

            ASSERT_EQ(expected.size(), actual.size());
            ASSERT_TRUE(expected == actual);

            // case-2
            expected = {
                " abc 123 ",
                std::string("\\") + exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP
            };
            std::cout << LOGGER_ID << " expected: " << TestUtils::toString(expected) << std::endl;

            format = TestUtils::join(expected);
            std::cout << LOGGER_ID << " format: '" << format << "'" << std::endl;

            actual = exqudens::log::util::FormatterUtils::splitFormat(format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            std::cout << LOGGER_ID << " actual: " << TestUtils::toString(actual) << std::endl;

            ASSERT_EQ(expected.size(), actual.size());
            ASSERT_TRUE(expected == actual);

            // case-3
            expected = {
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP,
                " abc 123 "
            };
            std::cout << LOGGER_ID << " expected: " << TestUtils::toString(expected) << std::endl;

            format = TestUtils::join(expected);
            std::cout << LOGGER_ID << " format: '" << format << "'" << std::endl;

            actual = exqudens::log::util::FormatterUtils::splitFormat(format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            std::cout << LOGGER_ID << " actual: " << TestUtils::toString(actual) << std::endl;

            ASSERT_EQ(expected.size(), actual.size());
            ASSERT_TRUE(expected == actual);

            // case-4
            expected = {
                " abc 123 ",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP,
                " def 456 "
            };
            std::cout << LOGGER_ID << " expected: " << TestUtils::toString(expected) << std::endl;

            format = TestUtils::join(expected);
            std::cout << LOGGER_ID << " format: '" << format << "'" << std::endl;

            actual = exqudens::log::util::FormatterUtils::splitFormat(format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            std::cout << LOGGER_ID << " actual: " << TestUtils::toString(actual) << std::endl;

            ASSERT_EQ(expected.size(), actual.size());
            ASSERT_TRUE(expected == actual);

            // case-5
            expected = {
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP,
                " ",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LEVEL,
                " ",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LOGGER,
                " [",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_THREAD,
                "] ",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_FUNCTION,
                "(",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_FILE,
                ":",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LINE,
                "): ",
                exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_MESSAGE
            };
            std::cout << LOGGER_ID << " expected: " << TestUtils::toString(expected) << std::endl;

            format = TestUtils::join(expected);
            std::cout << LOGGER_ID << " format: '" << format << "'" << std::endl;

            actual = exqudens::log::util::FormatterUtils::splitFormat(format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            std::cout << LOGGER_ID << " actual: " << TestUtils::toString(actual) << std::endl;

            ASSERT_EQ(expected.size(), actual.size());
            ASSERT_TRUE(expected == actual);

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    /*!
    * Test functions:
    * - toStringTimestamp
    */
    TEST_F(FormatterUtilsUnitTests, test_2) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::chrono::system_clock::time_point value = {};
            std::string format = {};
            unsigned short seconds = 0;
            std::map<unsigned short, long long> secondsDeviderMap = {};
            size_t size = 0;
            bool reverse = false;
            std::string actual = {};

            // case-1
            value = std::chrono::system_clock::now();
            format = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT;
            seconds = 9;
            secondsDeviderMap = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_SECONDS_DEVIDER_MAP;
            size = 0;
            reverse = false;

            actual = exqudens::log::util::FormatterUtils::toStringTimestamp(value, format, seconds, secondsDeviderMap, size, reverse);
            std::cout << LOGGER_ID << " actual: '" << actual << "'" << std::endl;

            ASSERT_EQ(29, actual.size());

            // case-2
            value = std::chrono::system_clock::now();
            format = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT;
            seconds = 0;
            secondsDeviderMap = {};
            size = 0;
            reverse = false;

            actual = exqudens::log::util::FormatterUtils::toStringTimestamp(value, format, seconds, secondsDeviderMap, size, reverse);
            std::cout << LOGGER_ID << " actual: '" << actual << "'" << std::endl;

            ASSERT_EQ(19, actual.size());

            // case-3
            value = std::chrono::system_clock::now();
            format = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT;
            seconds = 1;
            secondsDeviderMap = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_SECONDS_DEVIDER_MAP;
            size = 0;
            reverse = false;

            actual = exqudens::log::util::FormatterUtils::toStringTimestamp(value, format, seconds, secondsDeviderMap, size, reverse);
            std::cout << LOGGER_ID << " actual: '" << actual << "'" << std::endl;

            ASSERT_EQ(21, actual.size());

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}

#undef CALL_INFO
