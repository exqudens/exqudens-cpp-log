#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <vector>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Logger.hpp"
#include "exqudens/log/service/IHandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT LoggerService {

        private:

            unsigned short level = 0;
            std::vector<std::shared_ptr<IHandlerService>> handlers = {};
            bool configured = false;

        public:

            LoggerService();

            void configure(const exqudens::log::model::Logger& config);

            bool isConfigured();

            void write(
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            );

            ~LoggerService();

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    EXQUDENS_LOG_INLINE LoggerService::LoggerService() = default;

    EXQUDENS_LOG_INLINE void LoggerService::configure(const exqudens::log::model::Logger& config) {
        try {
            level = config.level;
            for (const exqudens::log::model::Handler& handlerConfig : config.handlers) {
                std::shared_ptr<exqudens::log::service::IHandlerService> handlerService = nullptr;

                if (handlerConfig.type == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE) {
                    handlerService = config.createConsoleHandlerFunction(handlerConfig);
                } else if (handlerConfig.type == exqudens::log::model::Constant::HANDLER_TYPE_FILE) {
                    handlerService = config.createFileHandlerFunction(handlerConfig);
                } else {
                    handlerService = config.createHandlerFunction(handlerConfig);
                }

                if (handlerService != nullptr) {
                    if (!handlerService->isConfigured()) {
                        throw std::runtime_error(CALL_INFO + ": handler: '" + handlerConfig.id + "' is not configured");
                    }
                    handlers.emplace_back(handlerService);
                }
            }
            configured = true;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE bool LoggerService::isConfigured() {
        return configured;
    }

    EXQUDENS_LOG_INLINE void LoggerService::write(
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) {
        try {
            if (level > this->level) {
                return;
            }
            exqudens::log::model::Data data = {};
            for (const std::shared_ptr<IHandlerService>& handler : handlers) {
                handler->write(
                    data,
                    file,
                    line,
                    function,
                    id,
                    level,
                    message
                );
            }
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE LoggerService::~LoggerService() = default;

}

#undef CALL_INFO
