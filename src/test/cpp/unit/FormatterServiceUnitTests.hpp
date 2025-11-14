#pragma once

#include <cstddef>
#include <string>
#include <any>
#include <memory>
#include <optional>
#include <vector>
#include <map>
#include <filesystem>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestUtils.hpp"

#include "exqudens/log/service/FormatterService.hpp"
#include "exqudens/Log.hpp"
#include "exqudens/log/util/ModelUtils.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    class FormatterServiceUnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "exqudens.FormatterServiceUnitTests";

    };

    TEST_F(FormatterServiceUnitTests, test_1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " bgn" << std::endl;

            exqudens::log::model::Configuration configuration = {};
            exqudens::log::model::Service serviceModel = {};
            std::map<std::string, exqudens::log::model::Logger> loggerMap = {};
            exqudens::log::model::Formatter config = {};
            exqudens::log::service::FormatterService service = {};
            exqudens::log::model::Data data = {};
            std::string expected = {};
            std::string actual = {};

            configuration = Log::defaultConfiguration("log/log.txt", 1073741824, {});
            serviceModel = Log::defaultServiceModel(configuration, {}, {}, {});
            loggerMap = exqudens::log::util::ModelUtils::toLoggerMap(serviceModel);
            config = loggerMap.at(exqudens::log::model::Constant::LOGGER_ID_ROOT).handlers.at(0).formatter;
            //config.parameters[exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP].size = 10;
            //config.parameters[exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP].reverse = true;
            config.parameters[exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FILE].base = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path().parent_path().generic_string();
            service = {};

            service.configure(config);
            std::cout << LOGGER_ID << " service.isConfigured: " << service.isConfigured() << std::endl;

            ASSERT_TRUE(service.isConfigured());

            actual = service.toString(
                data,
                __FILE__,
                __LINE__,
                __FUNCTION__,
                LOGGER_ID,
                4,
                "Abc123!"
            );
            std::cout << LOGGER_ID << " actual: '" << actual << "'" << std::endl;

            std::cout << LOGGER_ID << " " << '"' << testGroup << '.' << testCase << '"' << " end" << std::endl;
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}

#undef CALL_INFO
