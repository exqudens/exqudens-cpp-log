#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT FileHandlerUtils {

        public:

            FileHandlerUtils() = delete;

            ~FileHandlerUtils() = delete;

            static std::string getNextFileName(const std::string& currentFile, size_t maxSize);

    };

}

// implementation ---

#include <filesystem>
#include <stdexcept>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::string FileHandlerUtils::getNextFileName(const std::string& currentFile, size_t maxSize) {
        try {
            std::filesystem::path file(currentFile);

            if (!std::filesystem::exists(file)) {
                return file.generic_string();
            }

            size_t fileSize = std::filesystem::file_size(file);

            if (fileSize < maxSize) {
                return file.generic_string();
            }

            std::filesystem::path dir = file.parent_path();
            std::string fileName = file.stem().string();
            std::string fileExtension = file.extension().string();

            if (dir.empty()) {
                dir = std::filesystem::current_path();
            }

            size_t index = 1;

            while (std::filesystem::exists(file) && fileSize >= maxSize) {
                file = dir / (fileName + "-" + std::to_string(index++) + fileExtension);
                if (std::filesystem::exists(file)) {
                    fileSize = std::filesystem::file_size(file);
                } else {
                    fileSize = 0;
                }
            }

            return file.generic_string();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
