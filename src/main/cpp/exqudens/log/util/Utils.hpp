/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <string>
#include <vector>
#include <set>
#include <exception>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT Utils {

        public:

            Utils() = delete;

            ~Utils() = delete;

            static std::vector<std::string> toStringVector(const std::exception& exception, std::vector<std::string> previous = {}) noexcept;

            static std::vector<std::string> toStackTrace(const std::exception& exception) noexcept;

            static std::string toString(const std::exception& exception) noexcept;

            static std::string join(const std::string& prefix = "", const std::vector<std::string>& value = {}, const std::string& delimiter = "", const std::string& suffix = "") noexcept;

            static std::string joinSet(const std::string& prefix = "", const std::set<std::string>& value = {}, const std::string& delimiter = "", const std::string& suffix = "") noexcept;

    };

}

// implementation ---

#include <numeric>
#include <algorithm>
#include <sstream>

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::vector<std::string> Utils::toStringVector(const std::exception& exception, std::vector<std::string> previous) noexcept {
        previous.emplace_back(exception.what());
        try {
            std::rethrow_if_nested(exception);
            return previous;
        } catch (const std::exception& e) {
            return toStringVector(e, previous);
        } catch (...) {
            if (previous.empty()) {
                previous.emplace_back("UNHANDLED-CATCH-IN: 'exqudens::log::util::Utils::toStringVector'");
            }
            return previous;
        }
    }

    EXQUDENS_LOG_INLINE std::vector<std::string> Utils::toStackTrace(const std::exception& exception) noexcept {
        try {
            std::vector<std::string> elements = toStringVector(exception);
            if (elements.size() > 1) {
                std::ranges::reverse(elements);
            }
            return elements;
        } catch (const std::exception& e) {
            std::string errorMessage = join(
                "UNEXPECTED-EXCEPTION-IN: 'exqudens::log::util::Utils::toStackTrace",
                {
                    "(what: '",
                    e.what(),
                    "')"
                }
            );
            return {errorMessage};
        } catch (...) {
            return {"UNHANDLED-CATCH-IN: 'exqudens::log::util::Utils::toStackTrace'"};
        }
    }

    EXQUDENS_LOG_INLINE std::string Utils::toString(const std::exception& exception) noexcept {
        try {
            std::vector<std::string> stackTrace = toStackTrace(exception);
            std::ostringstream out;
            for (size_t i = 0; i < stackTrace.size(); i++) {
                out << stackTrace[i];
                if (i < stackTrace.size() - 1) {
                    out << std::endl;
                }
            }
            return out.str();
        } catch (const std::exception& e) {
            std::string errorMessage = join(
                "UNEXPECTED-EXCEPTION-IN: 'exqudens::log::util::Utils::toStackTrace",
                {
                    "(what: '",
                    e.what(),
                    "')"
                }
            );
            return errorMessage;
        } catch (...) {
            return {"UNHANDLED-CATCH-IN: 'exqudens::log::util::Utils::toStackTrace'"};
        }
    }

    EXQUDENS_LOG_INLINE std::string Utils::join(
        const std::string& prefix,
        const std::vector<std::string>& value,
        const std::string& delimiter,
        const std::string& suffix
    ) noexcept {
        try {
            if (value.empty()) {
                return prefix + suffix;
            }
            std::string result = std::accumulate(
                    value.begin(),
                    value.end(),
                    std::string(),
                    [&delimiter](const std::string& a, const std::string& b) {
                        return a + (a.empty() ? "" : delimiter) + b;
                    }
            );
            return prefix + result + suffix;
        } catch (...) {
            return prefix + suffix;
        }
    }

    EXQUDENS_LOG_INLINE std::string Utils::joinSet(
        const std::string& prefix,
        const std::set<std::string>& value,
        const std::string& delimiter,
        const std::string& suffix
    ) noexcept {
        try {
            std::vector<std::string> vectorValue(value.begin(), value.end());
            return join(prefix, vectorValue, delimiter, suffix);
        } catch (...) {
            return prefix + suffix;
        }
    }

}
