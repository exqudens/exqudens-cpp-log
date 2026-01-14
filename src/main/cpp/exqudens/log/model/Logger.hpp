/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Handler.hpp"
#include "exqudens/log/service/IHandlerService.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT Logger {

        std::string id;
        unsigned short level;
        std::vector<Handler> handlers;

        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createConsoleHandlerFunction;
        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createFileHandlerFunction;
        std::function<std::shared_ptr<exqudens::log::service::IHandlerService>(const exqudens::log::model::Handler&)> createHandlerFunction;

    };

}
