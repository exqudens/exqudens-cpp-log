#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/api/Logging.hpp"
#include "exqudens/log/model/Configuration.hpp"

namespace exqudens {

    class EXQUDENS_LOG_EXPORT Log {

        public:

            Log() = delete;

            ~Log() = delete;

            static std::map<std::string, exqudens::log::model::FormatterConfiguration::Parameter> defaultFormatterParameters();

            static std::map<std::string, exqudens::log::model::FormatterConfiguration> defaultFormatterConfigurations();

            static std::map<std::string, exqudens::log::model::HandlerConfiguration> defaultHandlerConfigurations(const std::string& formatter);

            static std::map<std::string, exqudens::log::model::LoggerConfiguration> defaultLoggerConfigurations(const std::vector<std::string>& handlers, const std::set<std::string>& loggerIds = {});

            static exqudens::log::model::Configuration defaultConfiguration(const std::set<std::string>& loggerIds = {});

            static std::map<unsigned short, std::string> loggerLevelIdNameMap() noexcept;

            static std::string configure(const std::set<std::string>& loggerIds = {});

            static bool isConfigured();

            static void reset();

    };

}
