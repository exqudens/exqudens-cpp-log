#include <stdexcept>
#include <filesystem>

#include "exqudens/Log.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> Log::defaultFormatterParameters() {
        try {
            std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> result = {};

            for (const std::string& id : exqudens::log::model::Constant::FORMATTER_PARAMETER_IDS) {
                exqudens::log::model::FormatterConfiguration::Parameter parameter = {};
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
                    parameter.name = true;
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

    std::map<std::string, exqudens::log::model::FormatterConfiguration> Log::defaultFormatterConfigurations() {
        try {
            std::map<std::string, exqudens::log::model::FormatterConfiguration> result = {};
            exqudens::log::model::FormatterConfiguration configuration = {};

            configuration.id = exqudens::log::model::Constant::FORMATTER_ID_FORMATTER;
            configuration.format = exqudens::log::model::Constant::FORMATTER_FORMAT_DEFAULT;
            configuration.parameters = defaultFormatterParameters();

            result[configuration.id] = configuration;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<std::string, exqudens::log::model::HandlerConfiguration> Log::defaultHandlerConfigurations(const std::string& formatter) {
        try {
            std::map<std::string, exqudens::log::model::HandlerConfiguration> result = {};

            exqudens::log::model::HandlerConfiguration consoleHandler = {};
            consoleHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.formatter = formatter;

            result[consoleHandler.id] = consoleHandler;

            exqudens::log::model::HandlerConfiguration fileHandler = {};
            fileHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.formatter = formatter;

            result[fileHandler.id] = fileHandler;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<std::string, exqudens::log::model::LoggerConfiguration> Log::defaultLoggerConfigurations(const std::vector<std::string>& handlers, const std::set<std::string>& loggerIds) {
        try {
            std::map<std::string, exqudens::log::model::LoggerConfiguration> result = {};

            exqudens::log::model::LoggerConfiguration logger = {};
            logger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
            logger.level = 999;
            logger.handlers = handlers;

            result[logger.id] = logger;

            for (const std::string& loggerId : loggerIds) {
                exqudens::log::model::LoggerConfiguration loggerConfiguration = {};
                loggerConfiguration.id = loggerId;
                loggerConfiguration.level = logger.level;
                loggerConfiguration.handlers = logger.handlers;

                result[loggerConfiguration.id] = loggerConfiguration;
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    exqudens::log::model::Configuration Log::defaultConfiguration(const std::set<std::string>& loggerIds) {
        try {
            exqudens::log::model::Configuration output = {};

            output.id = exqudens::log::model::Constant::CONFIGURATION_ID_DEFAULT;
            output.formatters = defaultFormatterConfigurations();
            output.handlers = defaultHandlerConfigurations(exqudens::log::model::Constant::FORMATTER_ID_FORMATTER);
            output.loggers = defaultLoggerConfigurations({exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE, exqudens::log::model::Constant::HANDLER_TYPE_FILE}, loggerIds);

            return output;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<unsigned short, std::string> Log::loggerLevelIdNameMap() noexcept {
        return exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP;
    }

    std::string Log::configure(const std::set<std::string>& loggerIds) {
        try {
            exqudens::log::model::Configuration configuration = defaultConfiguration(loggerIds);
            return exqudens::log::api::Logging::configure(configuration);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    bool Log::isConfigured() {
        try {
            return exqudens::log::api::Logging::isConfigured();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    void Log::reset() {
        try {
            exqudens::log::api::Logging::reset();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
