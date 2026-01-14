/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <string>
#include <optional>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include <thread>
#include <filesystem>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT FormatterUtils {

        public:

            FormatterUtils() = delete;

            ~FormatterUtils() = delete;

            static std::vector<std::string> splitFormat(const std::string& format, const std::set<std::string>& targets, char escape);

            static std::string toStringTimestamp(const std::chrono::system_clock::time_point& value, const std::string& format, unsigned short seconds, const std::map<unsigned short, long long>& secondsDeviderMap, size_t size, bool reverse);

            static std::string toStringLevel(unsigned short value, bool name, const std::map<unsigned short, std::string>& levelNameMap, size_t size, bool reverse);

            static std::string toStringThread(const std::thread::id& value, size_t size, bool reverse);

            static std::string toStringLogger(const std::string& value, size_t size, bool reverse);

            static std::string toStringFunction(const std::string& value, size_t size, bool reverse);

            static std::string toStringFile(const std::string& value, const std::string& base, bool name, size_t size, bool reverse);

            static std::string toStringLine(size_t value, size_t size, bool reverse);

            static std::string toStringMessage(const std::string& value, size_t size, bool reverse);

        private:

            static std::optional<std::pair<size_t, std::string>> splitFormatFind(const std::string& format, const std::vector<std::string>& targets);

            static std::string toStringSizeReverse(const std::string& value, size_t size, bool reverse);

    };

}

// implementation ---

#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::vector<std::string> FormatterUtils::splitFormat(const std::string& format, const std::set<std::string>& targets, char escape) {
        try {
            std::vector<std::string> internalTargets = {};
            for (const std::string& target : targets) {
                std::string internalTarget1 = {};
                internalTarget1 += escape;
                internalTarget1 += target;
                std::string internalTarget2 = target;
                internalTargets.emplace_back(internalTarget1);
                internalTargets.emplace_back(internalTarget2);
            }
            std::vector<std::string> result = {};
            std::string s = format;
            std::optional<std::pair<size_t, std::string>> targetEntry = splitFormatFind(s, internalTargets);
            size_t p = targetEntry ? targetEntry.value().first : std::string::npos;
            std::string token = "";
            while (targetEntry) {
                token = s.substr(0, p);
                if (!token.empty()) {
                    result.emplace_back(token);
                }
                s.erase(0, p + targetEntry.value().second.size());
                result.emplace_back(targetEntry.value().second);

                targetEntry = splitFormatFind(s, internalTargets);
                p = targetEntry ? targetEntry.value().first : std::string::npos;
            }
            token = s.substr(0, p);
            if (!token.empty()) {
                result.emplace_back(token);
            }
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringTimestamp(const std::chrono::system_clock::time_point& value, const std::string& format, unsigned short seconds, const std::map<unsigned short, long long>& secondsDeviderMap, size_t size, bool reverse) {
        try {
            seconds = seconds > 9 ? 9 : seconds;

            std::string result = {};

            time_t valueTime = std::chrono::system_clock::to_time_t(value);
            std::tm* timeInfo = std::localtime(&valueTime);
            if (timeInfo == nullptr) {
                throw std::runtime_error(CALL_INFO + ": 'timeInfo' is null");
            }
            std::ostringstream outputStream;
            outputStream << std::put_time(timeInfo, format.c_str());
            if (seconds > 0) {
                std::chrono::system_clock::duration valueSinceEpoch = value.time_since_epoch();
                std::chrono::nanoseconds valueSinceEpochNanoSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(valueSinceEpoch);
                valueSinceEpochNanoSeconds = valueSinceEpochNanoSeconds % 1000000000;
                if (seconds < 9) {
                    long long devider = secondsDeviderMap.at(seconds);
                    valueSinceEpochNanoSeconds = valueSinceEpochNanoSeconds / devider;
                }
                outputStream << '.' << std::setfill('0') << std::setw(seconds) << valueSinceEpochNanoSeconds.count();
            }
            result = outputStream.str();

            result = toStringSizeReverse(result, size, reverse);

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringLevel(unsigned short value, bool name, const std::map<unsigned short, std::string>& levelNameMap, size_t size, bool reverse) {
        try {
            std::string result = {};

            if (name && levelNameMap.contains(value)) {
                result = levelNameMap.at(value);
            } else {
                result = std::to_string(value);
            }

            result = toStringSizeReverse(result, size, reverse);

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringThread(const std::thread::id& value, size_t size, bool reverse) {
        try {
            std::string result = {};

            std::ostringstream outputStream;
            outputStream << value;
            result = outputStream.str();

            result = toStringSizeReverse(result, size, reverse);

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringLogger(const std::string& value, size_t size, bool reverse) {
        try {
            std::string result = value;
            result = toStringSizeReverse(result, size, reverse);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringFunction(const std::string& value, size_t size, bool reverse) {
        try {
            std::string result = value;
            result = toStringSizeReverse(result, size, reverse);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringFile(const std::string& value, const std::string& base, bool name, size_t size, bool reverse) {
        try {
            std::string result = {};

            std::filesystem::path valuePath(value);
            if (name) {
                result = valuePath.filename().string();
            } else {
                if (base.empty()) {
                    result = valuePath.generic_string();
                } else {
                    std::filesystem::path basePath(base);
                    std::filesystem::path relativePath = std::filesystem::relative(valuePath, basePath);
                    if (relativePath.empty()) {
                        result = valuePath.generic_string();
                    } else {
                        result = relativePath.generic_string();
                    }
                }
            }

            result = toStringSizeReverse(result, size, reverse);

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringLine(size_t value, size_t size, bool reverse) {
        try {
            std::string result = std::to_string(value);
            result = toStringSizeReverse(result, size, reverse);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringMessage(const std::string& value, size_t size, bool reverse) {
        try {
            std::string result = value;
            result = toStringSizeReverse(result, size, reverse);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::optional<std::pair<size_t, std::string>> FormatterUtils::splitFormatFind(const std::string& format, const std::vector<std::string>& targets) {
        try {
            std::optional<std::pair<size_t, std::string>> result = {};
            for (const std::string& target : targets) {
                size_t index = format.find(target);
                if (index != std::string::npos) {
                    if (result) {
                        if (index < result.value().first) {
                            std::pair<size_t, std::string> entry = {index, target};
                            result = entry;
                        }
                    } else {
                        std::pair<size_t, std::string> entry = {index, target};
                        result = entry;
                    }
                }
            }
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string FormatterUtils::toStringSizeReverse(const std::string& value, size_t size, bool reverse) {
        try {
            std::string result = value;
            if (size == 0 || value.size() <= size) {
                return result;
            } else {
                if (reverse) {
                    result = result.substr(value.size() - size);
                } else {
                    result.resize(size);
                }
            }
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
