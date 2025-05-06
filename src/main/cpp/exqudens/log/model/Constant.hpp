#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_EXPORT Constant {

        inline static const std::string HANDLER_TYPE_CONSOLE = "console";
        inline static const std::string HANDLER_TYPE_FILE = "file";

        inline static const std::string LOGGER_ID_ROOT = "root";

        inline static const std::string CONFIGURATION_ID_DEFAULT = "default";

    };

}
