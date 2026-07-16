/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Configuration.hpp"
#include "exqudens/log/model/Service.hpp"
#include "exqudens/log/model/Logger.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT ModelUtils {

        public:

            ModelUtils() = delete;

            ~ModelUtils() = delete;

            static std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> defaultFormatterParameters(
                const std::string& timestampFormat,
                uint16_t timestampFormatSecondsDivider
            );

            static std::map<std::string, exqudens::log::model::FormatterConfiguration> defaultFormatterConfigurations(
                const std::string& format,
                const std::string& timestampFormat,
                uint16_t timestampFormatSecondsDivider
            );

            static std::map<std::string, exqudens::log::model::HandlerConfiguration> defaultHandlerConfigurations(
                const std::string& file,
                size_t fileSize,
                const std::string& formatter
            );

            static std::map<std::string, exqudens::log::model::LoggerConfiguration> defaultLoggerConfigurations(
                const std::vector<std::string>& handlers,
                const std::map<std::string, uint16_t>& loggerIdLevelMap
            );

            static exqudens::log::model::Configuration defaultConfiguration(
                const std::string& file,
                size_t fileSize,
                const std::map<std::string, uint16_t>& loggerIdLevelMap,
                const std::string& format,
                const std::string& timestampFormat,
                uint16_t timestampFormatSecondsDivider
            );

            static exqudens::log::model::Service defaultServiceModel(
                const exqudens::log::model::Configuration& config,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
            );

            static std::map<std::string, exqudens::log::model::Logger> toLoggerMap(const exqudens::log::model::Service& config);

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>

#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> ModelUtils::defaultFormatterParameters(
        const std::string& timestampFormat,
        uint16_t timestampFormatSecondsDivider
    ) {
        try {
            std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> result = {};

            for (const std::string& id : exqudens::log::model::Constant::FORMATTER_PARAMETER_IDS) {
                exqudens::log::model::FormatterConfiguration::Parameter parameter = {};
                parameter.id = id;

                if (id == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP) {
                    parameter.format = timestampFormat;
                    parameter.seconds = timestampFormatSecondsDivider;
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

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::FormatterConfiguration> ModelUtils::defaultFormatterConfigurations(
        const std::string& format,
        const std::string& timestampFormat,
        uint16_t timestampFormatSecondsDivider
    ) {
        try {
            std::map<std::string, exqudens::log::model::FormatterConfiguration> result = {};
            exqudens::log::model::FormatterConfiguration configuration = {};

            configuration.id = exqudens::log::model::Constant::FORMATTER_ID_FORMATTER;
            configuration.format = format;
            configuration.parameters = defaultFormatterParameters(timestampFormat, timestampFormatSecondsDivider);

            result[configuration.id] = configuration;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::HandlerConfiguration> ModelUtils::defaultHandlerConfigurations(
        const std::string& file,
        size_t fileSize,
        const std::string& formatter
    ) {
        try {
            std::map<std::string, exqudens::log::model::HandlerConfiguration> result = {};

            exqudens::log::model::HandlerConfiguration consoleHandler = {};
            consoleHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE;
            consoleHandler.level = exqudens::log::model::Constant::LOGGER_LEVEL_ID_TRACE;
            consoleHandler.stream = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAM_OUT;
            consoleHandler.formatter = formatter;

            result[consoleHandler.id] = consoleHandler;

            exqudens::log::model::HandlerConfiguration fileHandler = {};
            fileHandler.id = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.type = exqudens::log::model::Constant::HANDLER_TYPE_FILE;
            fileHandler.level = exqudens::log::model::Constant::LOGGER_LEVEL_ID_TRACE;
            fileHandler.file = file;
            fileHandler.size = fileSize;
            fileHandler.formatter = formatter;

            result[fileHandler.id] = fileHandler;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::LoggerConfiguration> ModelUtils::defaultLoggerConfigurations(
        const std::vector<std::string>& handlers,
        const std::map<std::string,
        uint16_t>& loggerIdLevelMap
    ) {
        try {
            std::map<std::string, exqudens::log::model::LoggerConfiguration> result = {};

            exqudens::log::model::LoggerConfiguration logger = {};
            logger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
            uint16_t loggerLevel = exqudens::log::model::Constant::LOGGER_LEVEL_ID_INFO;
            if (loggerIdLevelMap.contains(logger.id) && exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.contains(loggerIdLevelMap.at(logger.id))) {
                loggerLevel = loggerIdLevelMap.at(logger.id);
            }
            logger.level = loggerLevel;
            logger.handlers = handlers;

            result[logger.id] = logger;

            for (const std::pair<std::string, uint16_t>& entry : loggerIdLevelMap) {
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

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration ModelUtils::defaultConfiguration(
        const std::string& file,
        size_t fileSize,
        const std::map<std::string, uint16_t>& loggerIdLevelMap,
        const std::string& format,
        const std::string& timestampFormat,
        uint16_t timestampFormatSecondsDivider
    ) {
        try {
            exqudens::log::model::Configuration output = {};

            output.id = exqudens::log::model::Constant::CONFIGURATION_ID_DEFAULT;
            output.formatters = defaultFormatterConfigurations(format, timestampFormat, timestampFormatSecondsDivider);
            output.handlers = defaultHandlerConfigurations(file, fileSize, exqudens::log::model::Constant::FORMATTER_ID_FORMATTER);
            output.loggers = defaultLoggerConfigurations({exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE, exqudens::log::model::Constant::HANDLER_TYPE_FILE}, loggerIdLevelMap);

            return output;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Service ModelUtils::defaultServiceModel(
        const exqudens::log::model::Configuration& config,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
    ) {
        try {
            exqudens::log::model::Service result = {};

            result.id = config.id;
            result.formatters = config.formatters;
            result.handlers = config.handlers;
            result.loggers = config.loggers;
            result.createConsoleHandlerFunction = createConsoleHandlerFunction;
            result.createFileHandlerFunction = createFileHandlerFunction;
            result.createHandlerFunction = createHandlerFunction;

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::Logger> ModelUtils::toLoggerMap(const exqudens::log::model::Service& config) {
        try {
            std::map<std::string, exqudens::log::model::Logger> result = {};

            for (const auto& loggerEntry : config.loggers) {
                exqudens::log::model::Logger logger = {};
                logger.id = loggerEntry.second.id;
                logger.level = loggerEntry.second.level;
                logger.handlers = {};
                logger.createConsoleHandlerFunction = config.createConsoleHandlerFunction;
                logger.createFileHandlerFunction = config.createFileHandlerFunction;
                logger.createHandlerFunction = config.createHandlerFunction;

                for (const std::string& handlerId : loggerEntry.second.handlers) {
                    exqudens::log::model::Handler handler = {};

                    if (!config.handlers.contains(handlerId)) {
                        throw std::runtime_error(CALL_INFO + ": configuration missing handler id: '" + handlerId + "'");
                    }

                    handler.id = handlerId;
                    handler.type = config.handlers.at(handler.id).type;
                    handler.level = config.handlers.at(handler.id).level;
                    handler.stream = config.handlers.at(handler.id).stream;
                    handler.file = config.handlers.at(handler.id).file;
                    handler.size = config.handlers.at(handler.id).size;

                    std::string formatterId = config.handlers.at(handler.id).formatter;

                    if (!config.formatters.contains(formatterId)) {
                        throw std::runtime_error(CALL_INFO + ": configuration missing formatter id: '" + handler.id + "'");
                    }

                    exqudens::log::model::Formatter formatter = {};
                    formatter.id = formatterId;
                    formatter.format = config.formatters.at(formatter.id).format;
                    formatter.parameters = {};
                    for (const auto& formatterParameterEntry : config.formatters.at(formatter.id).parameters) {
                        exqudens::log::model::Formatter::Parameter parameter = {};
                        parameter.id = formatterParameterEntry.second.id;
                        parameter.format = formatterParameterEntry.second.format;
                        parameter.seconds = formatterParameterEntry.second.seconds;
                        parameter.base = formatterParameterEntry.second.base;
                        parameter.name = formatterParameterEntry.second.name;
                        parameter.size = formatterParameterEntry.second.size;
                        parameter.reverse = formatterParameterEntry.second.reverse;
                        formatter.parameters[parameter.id] = parameter;
                    }
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
