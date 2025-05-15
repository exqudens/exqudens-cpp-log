#pragma once

#include <string>
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

            static log::model::Configuration defaultConfiguration(const std::set<std::string>& loggerIds = {});

            static std::map<unsigned short, std::string> loggerLevelIdNameMap() noexcept;

    };

}
