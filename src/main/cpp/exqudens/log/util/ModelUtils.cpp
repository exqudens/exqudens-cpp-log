#include <optional>
#include <stdexcept>
#include <filesystem>

#include "exqudens/log/util/ModelUtils.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    std::map<std::string, exqudens::log::model::Logger> ModelUtils::toLoggerMap(const exqudens::log::model::Configuration& configuration) {
        try {
            std::map<std::string, exqudens::log::model::Logger> result = {};

            if (!configuration.loggers.contains(exqudens::log::model::Constant::LOGGER_ID_ROOT)) {
                throw std::runtime_error(CALL_INFO + ": configuration missing logger id: '" + exqudens::log::model::Constant::LOGGER_ID_ROOT + "'");
            }

            for (const std::pair<std::string, exqudens::log::model::LoggerConfiguration>& loggerEntry : configuration.loggers) {
                exqudens::log::model::Logger logger = {};
                logger.id = loggerEntry.second.id;
                logger.level = loggerEntry.second.level;
                logger.handlers = {};

                for (const std::string& handlerId : loggerEntry.second.handlers) {
                    exqudens::log::model::Handler handler = {};

                    if (!configuration.handlers.contains(handlerId)) {
                        throw std::runtime_error(CALL_INFO + ": configuration missing handler id: '" + handlerId + "'");
                    }

                    handler.id = handlerId;
                    handler.type = configuration.handlers.at(handler.id).type;

                    std::string formatterId = configuration.handlers.at(handler.id).formatter;

                    if (!configuration.formatters.contains(formatterId)) {
                        throw std::runtime_error(CALL_INFO + ": configuration missing formatter id: '" + handler.id + "'");
                    }

                    exqudens::log::model::Formatter formatter = {};
                    formatter.id = formatterId;
                    formatter.format = configuration.formatters.at(formatter.id).format;
                    handler.formatter = formatter;

                    logger.handlers.emplace_back(handler);
                }

                result.insert({logger.id, logger});
            }

            if (result.empty()) {
                throw std::runtime_error(CALL_INFO + ": configuration is empty");
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
