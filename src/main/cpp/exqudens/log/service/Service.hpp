#pragma once

#include <cstddef>
#include <string>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Service.hpp"
#include "exqudens/log/service/LoggerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT Service {

        private:

            std::map<std::string, LoggerService> loggers = {};
            bool configured = false;

        public:

            Service();

            void configure(const exqudens::log::model::Service& config);

            bool isConfigured();

            void write(
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) noexcept;

            ~Service();

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/util/Utils.hpp"
#include "exqudens/log/util/ModelUtils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    EXQUDENS_LOG_INLINE Service::Service() = default;

    EXQUDENS_LOG_INLINE void Service::configure(const exqudens::log::model::Service& config) {
        try {
            std::map<std::string, exqudens::log::model::Logger> loggerMap = exqudens::log::util::ModelUtils::toLoggerMap(config);
            for (const std::pair<std::string, exqudens::log::model::Logger>& entry : loggerMap) {
                LoggerService logger;
                logger.configure(entry.second);
                if (!logger.isConfigured()) {
                    throw std::runtime_error(CALL_INFO + ": logger: '" + entry.second.id + "' is not configured");
                }
                loggers.insert({entry.second.id, logger});
            }
            configured = true;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE bool Service::isConfigured() {
        return configured;
    }

    EXQUDENS_LOG_INLINE void Service::write(
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) noexcept {
        try {
            if (!isConfigured()) {
                throw std::runtime_error(CALL_INFO + ": not configured");
            }

            if (!loggers.at(exqudens::log::model::Constant::LOGGER_ID_ROOT).isConfigured()) {
                throw std::runtime_error(CALL_INFO + ": logger '" + exqudens::log::model::Constant::LOGGER_ID_ROOT + "' not configured");
            }

            if (!loggers.contains(id)) {
                loggers.at(exqudens::log::model::Constant::LOGGER_ID_ROOT).write(
                    file,
                    line,
                    function,
                    id,
                    level,
                    "missing configuration"
                );
                return;
            }

            if (!loggers.at(id).isConfigured()) {
                throw std::runtime_error(CALL_INFO + ": logger '" + exqudens::log::model::Constant::LOGGER_ID_ROOT + "' not configured");
            }

            loggers.at(id).write(
                file,
                line,
                function,
                id,
                level,
                message
            );
        } catch (const std::exception& e) {
            std::cerr << exqudens::log::util::Utils::toString(e) << std::endl;
        } catch (...) {
            std::cerr << "UNHANDLED-CATCH-IN: 'exqudens::log::service::Service::write'" << std::endl;
        }
    }

    EXQUDENS_LOG_INLINE Service::~Service() = default;

}

#undef CALL_INFO
