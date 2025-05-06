#pragma once

#include <string>
#include <vector>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Handler.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_EXPORT Logger {

        std::string id;
        unsigned short level;
        std::vector<Handler> handlers;

    };

}
