#pragma once

#include <string>
#include <vector>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/api/Logging.hpp"
#include "exqudens/log/model/Configuration.hpp"

#ifndef EXQUDENS_LOG_TRACE
#define EXQUDENS_LOG_TRACE(id) EXQUDENS_LOG(id, 6)
#endif

#ifndef EXQUDENS_LOG_DEBUG
#define EXQUDENS_LOG_DEBUG(id) EXQUDENS_LOG(id, 5)
#endif

#ifndef EXQUDENS_LOG_INFO
#define EXQUDENS_LOG_INFO(id) EXQUDENS_LOG(id, 4)
#endif

#ifndef EXQUDENS_LOG_WARNING
#define EXQUDENS_LOG_WARNING(id) EXQUDENS_LOG(id, 3)
#endif

#ifndef EXQUDENS_LOG_ERROR
#define EXQUDENS_LOG_ERROR(id) EXQUDENS_LOG(id, 2)
#endif

#ifndef EXQUDENS_LOG_FATAL
#define EXQUDENS_LOG_FATAL(id) EXQUDENS_LOG(id, 1)
#endif

namespace exqudens {

    class EXQUDENS_LOG_EXPORT Log {

        public:

            Log() = delete;

            ~Log() = delete;

            static std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> defaultFormatterParameters();

            static std::map<std::string, exqudens::log::model::FormatterConfiguration> defaultFormatterConfigurations();

            static std::map<std::string, exqudens::log::model::HandlerConfiguration> defaultHandlerConfigurations(const std::string& file, size_t fileSize, const std::string& formatter);

            static std::map<std::string, exqudens::log::model::LoggerConfiguration> defaultLoggerConfigurations(const std::vector<std::string>& handlers, const std::map<std::string, unsigned short>& loggerIdLevelMap = {});

            static exqudens::log::model::Configuration defaultConfiguration(const std::string& file = "log/log.txt", size_t fileSize = 1024, const std::map<std::string, unsigned short>& loggerIdLevelMap = {});

            static std::map<unsigned short, std::string> loggerLevelIdNameMap() noexcept;

            static std::string configure(const std::string& file = "log/log.txt", size_t fileSize = 1024, const std::map<std::string, unsigned short>& loggerIdLevelMap = {});

            static bool isConfigured();

            static void reset();

    };

}
