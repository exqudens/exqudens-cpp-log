#pragma once

#include <string>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/FormatterConfiguration.hpp"
#include "exqudens/log/model/HandlerConfiguration.hpp"
#include "exqudens/log/model/LoggerConfiguration.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT Configuration {

        std::string id;
        std::map<std::string, FormatterConfiguration> formatters;
        std::map<std::string, HandlerConfiguration> handlers;
        std::map<std::string, LoggerConfiguration> loggers;

    };

}
