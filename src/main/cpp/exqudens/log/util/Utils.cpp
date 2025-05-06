#include <numeric>
#include <algorithm>
#include <sstream>

#include "exqudens/log/util/Utils.hpp"

namespace exqudens::log::util {

    std::vector<std::string> Utils::toStringVector(const std::exception& exception, std::vector<std::string> previous) noexcept {
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

    std::vector<std::string> Utils::toStackTrace(const std::exception& exception) noexcept {
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

    std::string Utils::toString(const std::exception& exception) noexcept {
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

    std::string Utils::join(
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
            return result;
        } catch (...) {
            return prefix + suffix;
        }
    }

}
