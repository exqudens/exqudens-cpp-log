/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"

#include <exqudens/log/api/Logging.hpp>

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

            static std::map<uint16_t, std::string> loggerLevelIdNameMap() noexcept;

            static std::vector<std::pair<uint16_t, std::string>> loggerLevelIdNameVector() noexcept;

            static std::string configure(
                const std::string& file = "log/log.txt",
                size_t fileSize = 1073741824,
                const std::set<std::string>& loggerIdSet = {},
                const std::map<std::string, uint16_t>& loggerIdLevelMap = {},
                const std::string& format = "${timestamp} ${level} ${logger} [${thread}] ${function}(${file}:${line}): ${message}",
                const std::string& timestampFormat = "%Y-%m-%d %H:%M:%S",
                uint16_t timestampFormatSecondsDivider = 9,
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
#include "exqudens/log/util/ModelUtils.hpp"
#include "exqudens/log/util/Utils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens {

    EXQUDENS_LOG_INLINE std::map<uint16_t, std::string> Log::loggerLevelIdNameMap() noexcept {
        return exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP;
    }

    EXQUDENS_LOG_INLINE std::vector<std::pair<uint16_t, std::string>> Log::loggerLevelIdNameVector() noexcept {
        return std::vector<std::pair<uint16_t, std::string>>(
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.begin(),
            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP.end()
        );
    }

    EXQUDENS_LOG_INLINE std::string Log::configure(
        const std::string &file,
        size_t fileSize,
        const std::set<std::string>& loggerIdSet,
        const std::map<std::string, uint16_t>& loggerIdLevelMap,
        const std::string& format,
        const std::string& timestampFormat,
        uint16_t timestampFormatSecondsDivider,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
        const std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
    ) {
        try {
            std::map<std::string, uint16_t> internalLoggerIdLevelMap = loggerIdLevelMap;

            for (const std::string& loggerId : loggerIdSet) {
                internalLoggerIdLevelMap.try_emplace(loggerId, 0);
            }

            exqudens::log::model::Configuration configuration = exqudens::log::util::ModelUtils::defaultConfiguration(
                file,
                fileSize,
                internalLoggerIdLevelMap,
                format,
                timestampFormat,
                timestampFormatSecondsDivider
            );

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

            exqudens::log::model::Service service = exqudens::log::util::ModelUtils::defaultServiceModel(
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
        uint16_t level
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
        const uint16_t level,
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
