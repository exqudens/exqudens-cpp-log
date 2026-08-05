/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT FileUtils {

        public:

            FileUtils() = delete;

            ~FileUtils() = delete;

            static std::string readFileToString(const std::string& path);

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <fstream>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::string FileUtils::readFileToString(const std::string& path) {
        try {
            // Open in binary mode to get exact byte count and avoid character translation
            std::ifstream file(path, std::ios::binary | std::ios::ate);
            if (!file) {
                throw std::runtime_error(CALL_INFO + ": failed to open file: '" + path + "'");
            }

            // Get current position (which is at the end) to determine size
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::string buffer;
            buffer.resize(size);

            if (file.read(buffer.data(), size)) {
                return buffer;
            }

            return "";
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
