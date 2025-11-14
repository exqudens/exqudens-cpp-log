#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/FormatterConfiguration.hpp"
#include "exqudens/log/model/HandlerConfiguration.hpp"
#include "exqudens/log/model/LoggerConfiguration.hpp"
#include "exqudens/log/service/IHandlerService.hpp"
#include "exqudens/log/model/Handler.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT Service {

        std::string id;
        std::map<std::string, FormatterConfiguration> formatters;
        std::map<std::string, HandlerConfiguration> handlers;
        std::map<std::string, LoggerConfiguration> loggers;

        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createConsoleHandlerFunction;
        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createFileHandlerFunction;
        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createHandlerFunction;

    };

}
