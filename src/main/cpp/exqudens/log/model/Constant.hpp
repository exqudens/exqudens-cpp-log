#pragma once

#include <string>
#include <set>
#include <map>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_EXPORT Constant {

        inline static const std::string FORMATTER_PARAMETER_ID_TIMESTAMP = "timestamp";
        inline static const std::string FORMATTER_PARAMETER_ID_LEVEL = "level";
        inline static const std::string FORMATTER_PARAMETER_ID_THREAD = "thread";
        inline static const std::string FORMATTER_PARAMETER_ID_LOGGER = "logger";
        inline static const std::string FORMATTER_PARAMETER_ID_FUNCTION = "function";
        inline static const std::string FORMATTER_PARAMETER_ID_FILE = "file";
        inline static const std::string FORMATTER_PARAMETER_ID_LINE = "line";
        inline static const std::string FORMATTER_PARAMETER_ID_MESSAGE = "message";

        inline static const std::set<std::string> FORMATTER_PARAMETER_IDS = {
            FORMATTER_PARAMETER_ID_TIMESTAMP,
            FORMATTER_PARAMETER_ID_LEVEL,
            FORMATTER_PARAMETER_ID_THREAD,
            FORMATTER_PARAMETER_ID_LOGGER,
            FORMATTER_PARAMETER_ID_FUNCTION,
            FORMATTER_PARAMETER_ID_FILE,
            FORMATTER_PARAMETER_ID_LINE,
            FORMATTER_PARAMETER_ID_MESSAGE
        };

        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_BGN = "${";
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_END = "}";

        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_TIMESTAMP + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_LEVEL = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_LEVEL + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_THREAD = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_THREAD + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_LOGGER = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_LOGGER + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_FUNCTION = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_FUNCTION + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_FILE = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_FILE + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_LINE = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_LINE + FORMATTER_FORMAT_PLACE_HOLDER_END;
        inline static const std::string FORMATTER_FORMAT_PLACE_HOLDER_MESSAGE = FORMATTER_FORMAT_PLACE_HOLDER_BGN + FORMATTER_PARAMETER_ID_MESSAGE + FORMATTER_FORMAT_PLACE_HOLDER_END;

        inline static const std::set<std::string> FORMATTER_FORMAT_PLACE_HOLDERS = {
            FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP,
            FORMATTER_FORMAT_PLACE_HOLDER_LEVEL,
            FORMATTER_FORMAT_PLACE_HOLDER_THREAD,
            FORMATTER_FORMAT_PLACE_HOLDER_LOGGER,
            FORMATTER_FORMAT_PLACE_HOLDER_FUNCTION,
            FORMATTER_FORMAT_PLACE_HOLDER_FILE,
            FORMATTER_FORMAT_PLACE_HOLDER_LINE,
            FORMATTER_FORMAT_PLACE_HOLDER_MESSAGE
        };

        //"${timestamp} ${level} ${logger} [${thread}] ${function}(${file}:${line}): ${message}";
        inline static const std::string FORMATTER_FORMAT_DEFAULT = FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP
            + " "
            + FORMATTER_FORMAT_PLACE_HOLDER_LEVEL
            + " "
            + FORMATTER_FORMAT_PLACE_HOLDER_LOGGER
            + " ["
            + FORMATTER_FORMAT_PLACE_HOLDER_THREAD
            + "] "
            + FORMATTER_FORMAT_PLACE_HOLDER_FUNCTION
            + "("
            + FORMATTER_FORMAT_PLACE_HOLDER_FILE
            + ":"
            + FORMATTER_FORMAT_PLACE_HOLDER_LINE
            + "): "
            + FORMATTER_FORMAT_PLACE_HOLDER_MESSAGE
        ;

        inline static const std::string FORMATTER_PARAMETER_TIMESTAMP_FORMAT_DEFAULT = "%Y-%m-%d %H:%M:%S";

        inline static const std::map<unsigned short, long long> FORMATTER_PARAMETER_TIMESTAMP_SECONDS_DEVIDER_MAP = {
            {1, 100000000},
            {2, 10000000},
            {3, 1000000},
            {4, 100000},
            {5, 10000},
            {6, 1000},
            {7, 100},
            {8, 10}
        };

        inline static const std::string FORMATTER_ID_FORMATTER = "formatter";

        inline static const std::string HANDLER_TYPE_CONSOLE = "console";
        inline static const std::string HANDLER_TYPE_FILE = "file";

        inline static const std::string LOGGER_ID_ROOT = "root";

        inline static const std::string CONFIGURATION_ID_DEFAULT = "default";

        inline static const std::map<unsigned short, std::string> LOGGER_LEVEL_ID_NAME_MAP = {
            {1, "FATAL"},
            {2, "ERROR"},
            {3, "WARNING"},
            {4, "INFO"},
            {5, "DEBUG"},
            {6, "TRACE"}
        };

    };

}
