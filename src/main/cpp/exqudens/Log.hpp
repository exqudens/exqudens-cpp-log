#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"

#include <exqudens/log/api/Logging.hpp>

#include "exqudens/log/model/FormatterConfiguration.hpp"
#include "exqudens/log/model/HandlerConfiguration.hpp"
#include "exqudens/log/model/LoggerConfiguration.hpp"
#include "exqudens/log/model/Configuration.hpp"
#include "exqudens/log/model/Service.hpp"
#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/service/IHandlerService.hpp"

#ifndef EXQUDENS_LOG_TRACE
#define EXQUDENS_LOG_TRACE(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_TRACE)
#endif

#ifndef EXQUDENS_LOG_DEBUG
#define EXQUDENS_LOG_DEBUG(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_DEBUG)
#endif

#ifndef EXQUDENS_LOG_INFO
#define EXQUDENS_LOG_INFO(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_INFO)
#endif

#ifndef EXQUDENS_LOG_WARNING
#define EXQUDENS_LOG_WARNING(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_WARNING)
#endif

#ifndef EXQUDENS_LOG_ERROR
#define EXQUDENS_LOG_ERROR(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_ERROR)
#endif

#ifndef EXQUDENS_LOG_FATAL
#define EXQUDENS_LOG_FATAL(id) EXQUDENS_LOG(id, exqudens::log::model::Constant::LOGGER_LEVEL_ID_FATAL)
#endif

namespace exqudens {

    class EXQUDENS_LOG_API_EXPORT Log {

        public:

            Log() = delete;

            ~Log() = delete;

            static std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> defaultFormatterParameters();

            static std::map<std::string, exqudens::log::model::FormatterConfiguration> defaultFormatterConfigurations();

            static std::map<std::string, exqudens::log::model::HandlerConfiguration> defaultHandlerConfigurations(
                const std::string& file,
                size_t fileSize,
                const std::string& formatter
            );

            static std::map<std::string, exqudens::log::model::LoggerConfiguration> defaultLoggerConfigurations(
                const std::vector<std::string>& handlers,
                const std::map<std::string, unsigned short>& loggerIdLevelMap
            );

            static exqudens::log::model::Configuration defaultConfiguration(
                const std::string& file,
                size_t fileSize,
                const std::map<std::string,
                unsigned short>& loggerIdLevelMap
            );

            static exqudens::log::model::Service defaultServiceModel(
                const exqudens::log::model::Configuration& config,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
            );

            static std::map<unsigned short, std::string> loggerLevelIdNameMap() noexcept;

            static std::vector<std::pair<unsigned short, std::string>> loggerLevelIdNameVector() noexcept;

            static std::string configure(
                const std::string& file = "log/log.txt",
                size_t fileSize = 1073741824,
                const std::set<std::string>& loggerIdSet = {},
                const std::map<std::string, unsigned short>& loggerIdLevelMap = {},
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction = {},
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction = {},
                const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction = {}
            );

            static bool isConfigured();

            static void reset();

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <utility>
#include <iostream>

#include "exqudens/log/service/ConsoleHandlerService.hpp"
#include "exqudens/log/service/FileHandlerService.hpp"
#include "exqudens/log/service/Service.hpp"
#include "exqudens/log/util/Utils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> Log::defaultFormatterParameters() {
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

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::FormatterConfiguration> Log::defaultFormatterConfigurations() {
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

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::HandlerConfiguration> Log::defaultHandlerConfigurations(
        const std::string& file,
        size_t fileSize,
        const std::string& formatter
    ) {
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

    EXQUDENS_LOG_INLINE std::map<std::string, exqudens::log::model::LoggerConfiguration> Log::defaultLoggerConfigurations(
        const std::vector<std::string>& handlers,
        const std::map<std::string,
        unsigned short>& loggerIdLevelMap
    ) {
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

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration Log::defaultConfiguration(
        const std::string& file,
        size_t fileSize,
        const std::map<std::string, unsigned short>& loggerIdLevelMap
    ) {
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

    EXQUDENS_LOG_INLINE exqudens::log::model::Service Log::defaultServiceModel(
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

    EXQUDENS_LOG_INLINE std::map<unsigned short, std::string> Log::loggerLevelIdNameMap() noexcept {
        return exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP;
    }

    EXQUDENS_LOG_INLINE std::vector<std::pair<unsigned short, std::string>> Log::loggerLevelIdNameVector() noexcept {
        return std::vector<std::pair<unsigned short, std::string>>(
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.begin(),
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.end()
        );
    }

    EXQUDENS_LOG_INLINE std::string Log::configure(
        const std::string &file,
        size_t fileSize,
        const std::set<std::string>& loggerIdSet,
        const std::map<std::string, unsigned short>& loggerIdLevelMap,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
    ) {
        try {
            std::map<std::string, unsigned short> internalLoggerIdLevelMap = loggerIdLevelMap;

            for (const std::string& loggerId : loggerIdSet) {
                internalLoggerIdLevelMap.try_emplace(loggerId, 0);
            }

            exqudens::log::model::Configuration configuration = defaultConfiguration(file, fileSize, internalLoggerIdLevelMap);

            std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> internalCreateConsoleHandlerFunction = {};
            std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> internalCreateFileHandlerFunction = {};
            std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> internalCreateHandlerFunction = {};

            if (createConsoleHandlerFunction) {
                internalCreateConsoleHandlerFunction = createConsoleHandlerFunction;
            } else {
                internalCreateConsoleHandlerFunction = [](const exqudens::log::model::Handler& arg0) {
                    std::shared_ptr<exqudens::log::service::IHandlerService> result = nullptr;
                    result = std::make_unique<exqudens::log::service::ConsoleHandlerService>();
                    result->configure(arg0);
                    return result;
                };
            }

            if (createFileHandlerFunction) {
                internalCreateFileHandlerFunction = createFileHandlerFunction;
            } else {
                internalCreateFileHandlerFunction = [](const exqudens::log::model::Handler& arg0) {
                    std::shared_ptr<exqudens::log::service::IHandlerService> result = nullptr;
                    result = std::make_unique<exqudens::log::service::FileHandlerService>();
                    result->configure(arg0);
                    return result;
                };
            }

            exqudens::log::model::Service service = defaultServiceModel(
                configuration,
                internalCreateConsoleHandlerFunction,
                internalCreateFileHandlerFunction,
                createHandlerFunction
            );

            return exqudens::log::api::Logging::configure(service);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE bool Log::isConfigured() {
        try {
            return exqudens::log::api::Logging::isConfigured();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE void Log::reset() {
        try {
            exqudens::log::api::Logging::reset();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

namespace exqudens::log::api {

    EXQUDENS_LOG_INLINE Logging::Writer::Writer(
        std::string file,
        size_t line,
        std::string function,
        std::string id,
        unsigned short level
    ):
        file(std::move(file)),
        line(line),
        function(std::move(function)),
        id(std::move(id)),
        level(level) {
    }

    EXQUDENS_LOG_INLINE Logging::Writer::~Writer() {
        Logging::write(
            file,
            line,
            function,
            id,
            level,
            stream.str()
        );
    }

    EXQUDENS_LOG_INLINE std::string Logging::configure(const std::any& input) {
        try {
            if (input.type() != typeid(exqudens::log::model::Service)) {
                throw std::runtime_error(CALL_INFO + ": unsupported input type: '" + input.type().name() + "' supported type: '" + typeid(exqudens::log::model::Service).name() + "'");
            }
            exqudens::log::model::Service config = std::any_cast<exqudens::log::model::Service>(input);
            std::shared_ptr<exqudens::log::service::Service> service = std::make_shared<exqudens::log::service::Service>();
            service->configure(config);
            Logging::data = service;
            return config.id;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE bool Logging::isConfigured() {
        try {
            return Logging::data.has_value();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE void Logging::write(
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) noexcept {
        try {
            if (!Logging::isConfigured()) {
                std::cerr << "not configured" << std::endl;
                return;
            }

            if (Logging::data.type() != typeid(std::shared_ptr<exqudens::log::service::Service>)) {
                std::string errorMessage = exqudens::log::util::Utils::join(
                    "wrong type",
                    {
                        ": '",
                        Logging::data.type().name(),
                        "' expected type: '",
                        typeid(std::shared_ptr<exqudens::log::service::Service>).name(),
                        "'"
                    }
                );
                std::cerr << errorMessage << std::endl;
                return;
            }

            std::shared_ptr<exqudens::log::service::Service> service = std::any_cast<std::shared_ptr<exqudens::log::service::Service>>(Logging::data);

            service->write(
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
            std::cerr << "UNHANDLED-CATCH-IN: 'exqudens::log::api::Logging::write'" << std::endl;
        }
    }

    EXQUDENS_LOG_INLINE void Logging::reset() {
        try {
            Logging::data = {};
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
