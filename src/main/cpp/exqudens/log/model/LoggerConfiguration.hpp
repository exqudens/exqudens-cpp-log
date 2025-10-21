#pragma once

#include <string>
#include <vector>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT LoggerConfiguration {

        std::string id;
        unsigned short level;
        std::vector<std::string> handlers;

    };

}
