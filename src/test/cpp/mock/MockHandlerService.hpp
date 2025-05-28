#pragma once

#include <gmock/gmock.h>

#include "exqudens/log/service/HandlerService.hpp"

namespace exqudens::log::service {

    class MockHandlerService : public HandlerService {

        private:

            HandlerService real;

        public:

            MockHandlerService() {
                ON_CALL(*this, configure)
                .WillByDefault([this](const exqudens::log::model::Handler& config) {
                    real.HandlerService::configure(config);
                });

                ON_CALL(*this, isConfigured)
                .WillByDefault([this]() {
                    return real.HandlerService::isConfigured();
                });

                ON_CALL(*this, toString)
                .WillByDefault([this](exqudens::log::model::Data& data, const std::string& file, const size_t line, const std::string& function, const std::string& id, const unsigned short level, const std::string& message) {
                    return real.toString(data, file, line, function, id, level, message);
                });

                ON_CALL(*this, writeString)
                .WillByDefault([this](const std::string& value) {});

                ON_CALL(*this, write)
                .WillByDefault([this](exqudens::log::model::Data& data, const std::string& file, const size_t line, const std::string& function, const std::string& id, const unsigned short level, const std::string& message) {
                    std::string event = toString(data, file, line, function, id, level, message);
                    writeString(event);
                });
            }

            MOCK_METHOD(void, configure, (const exqudens::log::model::Handler&), (override));
            MOCK_METHOD(bool, isConfigured, (), (override));
            MOCK_METHOD(std::string, toString, (exqudens::log::model::Data&, const std::string&, const size_t, const std::string&, const std::string&, const unsigned short, const std::string&), (override));
            MOCK_METHOD(void, writeString, (const std::string&), (override));
            MOCK_METHOD(void, write, (exqudens::log::model::Data&, const std::string&, const size_t, const std::string&, const std::string&, const unsigned short, const std::string&), (override));

    };

}
