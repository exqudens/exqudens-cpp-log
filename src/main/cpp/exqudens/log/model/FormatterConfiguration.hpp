#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_EXPORT FormatterConfiguration {

        std::string id;
        std::string format;

    };

}
