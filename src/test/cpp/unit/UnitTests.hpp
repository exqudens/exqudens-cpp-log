#pragma once

#include <cstddef>
#include <string>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestUtils.hpp"

#include "exqudens/Log.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    class UnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.LogUnitTests";

    };

    TEST_F(UnitTests, test1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            exqudens::log::model::Configuration configuration = Log::defaultConfiguration({
                "test.logger.1"
            });
            std::string loggingConfig = log::api::Logging::configure(configuration);
            std::cout << LOGGER_ID << " loggingConfig: " << '"' << loggingConfig << '"' << std::endl;

            EXQUDENS_LOG("test.logger.1", 4) << "Abc123!";

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}

#undef CALL_INFO
