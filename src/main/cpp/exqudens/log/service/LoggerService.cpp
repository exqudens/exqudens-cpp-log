#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/service/LoggerService.hpp"
#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/service/ServiceFactory.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    LoggerService::LoggerService() = default;

    void LoggerService::configure(const exqudens::log::model::Logger& config) {
        try {
            level = config.level;
            for (const exqudens::log::model::Handler& handlerConfig : config.handlers) {
                std::shared_ptr<exqudens::log::service::IHandlerService> handlerService = nullptr;

                if (handlerConfig.type == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE) {
                    handlerService = ServiceFactory::getInstance().createConsoleHandler(handlerConfig);
                } else if (handlerConfig.type == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE) {
                    handlerService = ServiceFactory::getInstance().createFileHandler(handlerConfig);
                } else {
                    handlerService = ServiceFactory::getInstance().createHandler(handlerConfig);
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

    bool LoggerService::isConfigured() {
        return configured;
    }

    void LoggerService::write(
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
            for (const std::shared_ptr<IHandlerService>& handler : handlers) {
                handler->write(
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

    LoggerService::~LoggerService() = default;

}

#undef CALL_INFO
