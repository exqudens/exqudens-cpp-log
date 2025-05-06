#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/service/Service.hpp"
#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/util/Utils.hpp"
#include "exqudens/log/util/ModelUtils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    Service::Service() = default;

    void Service::configure(const exqudens::log::model::Configuration& configuration) {
        try {
            std::map<std::string, exqudens::log::model::Logger> loggerMap = exqudens::log::util::ModelUtils::toLoggerMap(configuration);
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

    bool Service::isConfigured() {
        return configured;
    }

    void Service::write(
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

    Service::~Service() = default;

}

#undef CALL_INFO
