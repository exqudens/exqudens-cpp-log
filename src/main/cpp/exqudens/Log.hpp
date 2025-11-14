#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"
#include "exqudens/log/api/Logging.hpp"
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
