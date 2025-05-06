#pragma once

#include <string>
#include <vector>
#include <exception>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_EXPORT Utils {

        public:

            Utils() = delete;

            ~Utils() = delete;

            static std::vector<std::string> toStringVector(const std::exception& exception, std::vector<std::string> previous = {}) noexcept;

            static std::vector<std::string> toStackTrace(const std::exception& exception) noexcept;

            static std::string toString(const std::exception& exception) noexcept;

            static std::string join(const std::string& prefix = "", const std::vector<std::string>& value = {}, const std::string& delimiter = "", const std::string& suffix = "") noexcept;

    };

}
