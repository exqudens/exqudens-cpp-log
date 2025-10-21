#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT FileHandlerUtils {

        public:

            static std::string getNextFileName(const std::string& currentFile, size_t maxSize);

            FileHandlerUtils() = delete;

            ~FileHandlerUtils() = delete;

    };

}
