#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "mock/MockHandlerService.hpp"
#include "exqudens/log/service/ServiceFactory.hpp"
#include "exqudens/Log.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    class LogUnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.LogUnitTests";

    };

    TEST_F(LogUnitTests, test_1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            std::vector<std::string> messages = {};

            std::shared_ptr<exqudens::log::service::MockHandlerService> mock = std::make_shared<exqudens::log::service::MockHandlerService>();

            EXPECT_CALL(*mock, configure).Times(testing::AtLeast(1));
            EXPECT_CALL(*mock, isConfigured).Times(testing::AtLeast(1));
            EXPECT_CALL(*mock, toString).Times(testing::AtLeast(1));
            EXPECT_CALL(*mock, writeString).WillRepeatedly([&messages](const std::string& value) { messages.emplace_back(value); });
            EXPECT_CALL(*mock, write).Times(testing::AtLeast(1));

            exqudens::log::service::ServiceFactory::init(
                [&mock](const exqudens::log::model::Handler& config) { mock->configure(config); return mock; },
                [&mock](const exqudens::log::model::Handler& config) { mock->configure(config); return mock; },
                {}
            );

            std::string loggingConfig = exqudens::Log::configure({
                "test.logger.1"
            });
            std::cout << LOGGER_ID << " loggingConfig: " << '"' << loggingConfig << '"' << std::endl;

            EXQUDENS_LOG("test.logger.1", 4) << "Abc123!";

            for (size_t i = 0; i < messages.size(); i++) {
                std::cout << LOGGER_ID << " messages[" << i << "]: " << '"' << messages.at(i) << '"' << std::endl;
            }

            Log::reset();

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}

#undef CALL_INFO
