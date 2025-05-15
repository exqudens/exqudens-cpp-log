#include <stdexcept>
#include <filesystem>

#include "exqudens/Log.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    std::map<std::string, log::model::FormatterConfiguration::Parameter> Log::defaultFormatterParameters() {
        try {
            std::map<std::string, log::model::FormatterConfiguration::Parameter> result = {};

            for (const std::string& id : exqudens::log::model::Constant::FORMATTER_PARAMETER_IDS) {
                log::model::FormatterConfiguration::Parameter parameter = {};
                parameter.id = id;

                if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP) {
                    parameter.format = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT;
                    parameter.seconds = 9;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LEVEL) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = true;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_THREAD) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LOGGER) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FUNCTION) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FILE) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LINE) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_MESSAGE) {
                    parameter.format = {};
                    parameter.seconds = 0;
                    parameter.base = {};
                    parameter.name = false;
                    parameter.size = 0;
                    parameter.reverse = false;
                } else {
                    throw std::runtime_error(CALL_INFO + ": unsupported parameter id: '" + id + "'");
                }

                result[parameter.id] = parameter;
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<std::string, log::model::FormatterConfiguration> Log::defaultFormatterConfigurations() {
        try {
            std::map<std::string, log::model::FormatterConfiguration> result = {};
            log::model::FormatterConfiguration configuration = {};

            configuration.id = exqudens::log::model::Constant::FORMATTER_ID_FORMATTER;
            configuration.format = exqudens::log::model::Constant::FORMATTER_FORMAT_DEFAULT;
            configuration.parameters = defaultFormatterParameters();

            result[configuration.id] = configuration;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    log::model::Configuration Log::defaultConfiguration(const std::set<std::string>& loggerIds) {
        try {
            log::model::Configuration output = {};
            output.id = exqudens::log::model::Constant::CONFIGURATION_ID_DEFAULT;
            output.formatters = defaultFormatterConfigurations();
            output.handlers = {};
            output.loggers = {};

            // formatters
            /* log::model::FormatterConfiguration formatter = {};
            formatter.id = "formatter";
            formatter.format = exqudens::log::model::Constant::FORMATTER_FORMAT_DEFAULT;
            formatter.parameters = {};

            log::model::FormatterConfiguration::Parameter formatterParameter = {};
            formatterParameter.id = exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP;
            formatterParameter.format = exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT;
            formatter.parameters[formatterParameter.id] = formatterParameter;

            output.formatters[formatter.id] = formatter; */

            // handlers
            log::model::HandlerConfiguration consoleHandler = {};
            consoleHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.formatter = output.formatters.at(exqudens::log::model::Constant::FORMATTER_ID_FORMATTER).id;

            /* log::model::HandlerConfiguration fileHandler = {};
            fileHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.formatter = formatter.id; */

            output.handlers[consoleHandler.id] = consoleHandler;
            //output.handlers[fileHandler.id] = fileHandler;

            // loggers
            log::model::LoggerConfiguration logger = {};
            logger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
            logger.level = 999;
            logger.handlers.emplace_back(consoleHandler.id);

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

    std::map<unsigned short, std::string> Log::loggerLevelIdNameMap() noexcept {
        return log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP;
    }

}

#undef CALL_INFO
