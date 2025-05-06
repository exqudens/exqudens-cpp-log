#include <stdexcept>
#include <filesystem>

#include "exqudens/Log.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    log::model::Configuration Log::defaultConfiguration(const std::set<std::string>& loggerIds) {
        try {
            log::model::FormatterConfiguration formatter = {};
            formatter.id = "formatter";
            formatter.format = "${datetime} ${level} [${thread}] ${function}(${file}:${line}): ${message}";

            log::model::HandlerConfiguration consoleHandler = {};
            consoleHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.formatter = formatter.id;

            /* log::model::HandlerConfiguration fileHandler = {};
            fileHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.formatter = formatter.id; */

            log::model::LoggerConfiguration logger = {};
            logger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
            logger.level = 999;
            logger.handlers.emplace_back(consoleHandler.id);

            log::model::Configuration output = {};
            output.id = exqudens::log::model::Constant::CONFIGURATION_ID_DEFAULT;

            output.formatters[formatter.id] = formatter;

            output.handlers[consoleHandler.id] = consoleHandler;
            //output.handlers[fileHandler.id] = fileHandler;

            output.loggers[logger.id] = logger;

            for (const std::string& loggerId : loggerIds) {
                exqudens::log::model::LoggerConfiguration loggerConfiguration = {};
                loggerConfiguration.id = loggerId;
                loggerConfiguration.level = logger.level;
                loggerConfiguration.handlers = logger.handlers;

                output.loggers[loggerConfiguration.id] = loggerConfiguration;
            }

            return output;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
