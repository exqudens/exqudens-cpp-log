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

    class EXQUDENS_LOG_EXPORT FormatterUtils {

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

            //static std::string getCurrentTimestampString(const std::string& format, unsigned short seconds, const std::map<unsigned short, long long>& secondsDeviderMap, size_t size, bool reverse);

            //static std::string getCurrentThreadString(size_t size, bool reverse);

        private:

            static std::optional<std::pair<size_t, std::string>> splitFormatFind(const std::string& format, const std::vector<std::string>& targets);

            static std::string toStringSizeReverse(const std::string& value, size_t size, bool reverse);

    };

}
