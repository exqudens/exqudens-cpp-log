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

    std::map<std::string, exqudens::log::model::HandlerConfiguration> Log::defaultHandlerConfigurations(const std::string& file, size_t fileSize, const std::string& formatter) {
        try {
            std::map<std::string, exqudens::log::model::HandlerConfiguration> result = {};

            exqudens::log::model::HandlerConfiguration consoleHandler = {};
            consoleHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.stream = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAM_OUT;
            consoleHandler.formatter = formatter;

            result[consoleHandler.id] = consoleHandler;

            exqudens::log::model::HandlerConfiguration fileHandler = {};
            fileHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.file = file;
            fileHandler.size = fileSize;
            fileHandler.formatter = formatter;

            result[fileHandler.id] = fileHandler;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<std::string, exqudens::log::model::LoggerConfiguration> Log::defaultLoggerConfigurations(const std::vector<std::string>& handlers, const std::map<std::string, unsigned short>& loggerIdLevelMap) {
        try {
            std::map<std::string, exqudens::log::model::LoggerConfiguration> result = {};

            exqudens::log::model::LoggerConfiguration logger = {};
            logger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
            unsigned short loggerLevel = exqudens::log::model::Constant::LOGGER_LEVEL_ID_INFO;
            if (loggerIdLevelMap.contains(logger.id) && exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.contains(loggerIdLevelMap.at(logger.id))) {
                loggerLevel = loggerIdLevelMap.at(logger.id);
            }
            logger.level = loggerLevel;
            logger.handlers = handlers;

            result[logger.id] = logger;

            for (const std::pair<std::string, unsigned short>& entry : loggerIdLevelMap) {
                if (entry.first == logger.id) {
                    continue;
                }
                exqudens::log::model::LoggerConfiguration loggerConfiguration = {};
                loggerConfiguration.id = entry.first;
                loggerConfiguration.level = logger.level;
                if (exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.contains(entry.second)) {
                    loggerConfiguration.level = entry.second;
                }
                loggerConfiguration.handlers = logger.handlers;

                result[loggerConfiguration.id] = loggerConfiguration;
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    exqudens::log::model::Configuration Log::defaultConfiguration(const std::string& file, size_t fileSize, const std::map<std::string, unsigned short>& loggerIdLevelMap) {
        try {
            exqudens::log::model::Configuration output = {};

            output.id = exqudens::log::model::Constant::CONFIGURATION_ID_DEFAULT;
            output.formatters = defaultFormatterConfigurations();
            output.handlers = defaultHandlerConfigurations(file, fileSize, exqudens::log::model::Constant::FORMATTER_ID_FORMATTER);
            output.loggers = defaultLoggerConfigurations({exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE, exqudens::log::model::Constant::HANDLER_TYPE_FILE}, loggerIdLevelMap);

            return output;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::map<unsigned short, std::string> Log::loggerLevelIdNameMap() noexcept {
        return exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP;
    }

    std::vector<std::pair<unsigned short, std::string>> Log::loggerLevelIdNameVector() noexcept {
        return std::vector<std::pair<unsigned short, std::string>>(
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.begin(),
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.end()
        );
    }

    std::string Log::configure(
        const std::string &file,
        size_t fileSize,
        const std::set<std::string>& loggerIdSet,
        const std::map<std::string, unsigned short>& loggerIdLevelMap
    ) {
        try {
            std::map<std::string, unsigned short> internalLoggerIdLevelMap = loggerIdLevelMap;
            for (const std::string& loggerId : loggerIdSet) {
                internalLoggerIdLevelMap.try_emplace(loggerId, 0);
            }
            exqudens::log::model::Configuration configuration = defaultConfiguration(file, fileSize, internalLoggerIdLevelMap);
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
