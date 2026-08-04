#pragma once

#include <cstddef>
#include <string>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Value.hpp"

namespace exqudens::log::util::json {

    class EXQUDENS_LOG_API_EXPORT Serializer {

        public:

            static std::string serialize(const Value& value, size_t indent = 0, const std::string& newline = "\n");

            static std::string escapeString(const std::string& value);

        private:

            static std::string getIndent(size_t level, size_t spacesPerLevel);

            static std::string serializeInternal(const Value& value, size_t indentLevel, size_t indentSpaces, const std::string& newline);

    };
}

// implementation ---

#include <filesystem>
#include <stdexcept>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <ios>

#include "exqudens/log/util/json/Array.hpp"
#include "exqudens/log/util/json/Object.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE std::string Serializer::serialize(const Value& value, size_t indent, const std::string& newline) {
        return serializeInternal(value, 0, indent, newline);
    }

    EXQUDENS_LOG_INLINE std::string Serializer::escapeString(const std::string& value) {
        std::string result = "";
        for (char c : value) {
            if (c == '"') {
                result += "\\\"";
            } else if (c == '\\') {
                result += "\\\\";
            } else if (c == '\b') {
                result += "\\b";
            } else if (c == '\f') {
                result += "\\f";
            } else if (c == '\n') {
                result += "\\n";
            } else if (c == '\r') {
                result += "\\r";
            } else if (c == '\t') {
                result += "\\t";
            } else {
                // Escape control characters below ASCII 32
                if (static_cast<unsigned char>(c) < 32) {
                    std::ostringstream ss;
                    ss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(c);
                    result += ss.str();
                } else {
                    result += c;
                }
            }
        }
        return result;
    }

    EXQUDENS_LOG_INLINE std::string Serializer::getIndent(size_t level, size_t spacesPerLevel) {
        if (spacesPerLevel == 0) {
            return "";
        }
        return std::string(level * spacesPerLevel, ' ');
    }

    EXQUDENS_LOG_INLINE std::string Serializer::serializeInternal(const Value& value, size_t indentLevel, size_t indentSpaces, const std::string& newline) {
        bool pretty = (indentSpaces > 0);
        std::string nl = pretty ? newline : "";
        std::string space_after_colon = pretty ? " " : "";

        return std::visit([&](const auto& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::nullptr_t>) {
                return "null";
            } else if constexpr (std::is_same_v<T, bool>) {
                return arg ? "true" : "false";
            } else if constexpr (std::is_same_v<T, long double>) {
                // Strips trailing zeros from std::to_string output
                std::string s = std::to_string(arg);
                s.erase(s.find_last_not_of('0') + 1, std::string::npos);
                if (s.back() == '.') {
                    s.pop_back();
                }
                return s;
            } else if constexpr (std::is_same_v<T, intmax_t>) {
                return std::to_string(arg);
            } else if constexpr (std::is_same_v<T, std::string>) {
                return "\"" + escapeString(arg) + "\"";
            } else if constexpr (std::is_same_v<T, Array>) {
                if (arg.empty()) {
                    return "[]";
                }

                std::string s = "[" + nl;
                for (size_t i = 0; i < arg.size(); ++i) {
                    s += getIndent(indentLevel + 1, indentSpaces);
                    s += serializeInternal(arg[i], indentLevel + 1, indentSpaces, newline);
                    if (i + 1 < arg.size()) {
                        s += ",";
                    }
                    s += nl;
                }
                s += getIndent(indentLevel, indentSpaces) + "]";
                return s;
            } else if constexpr (std::is_same_v<T, Object>) {
                if (arg.empty()) {
                    return "{}";
                }

                std::string s = "{" + nl;
                size_t i = 0;
                for (const auto& [k, v] : arg) {
                    s += getIndent(indentLevel + 1, indentSpaces);
                    s += "\"" + escapeString(k) + "\":" + space_after_colon;
                    s += serializeInternal(v, indentLevel + 1, indentSpaces, newline);
                    if (++i < arg.size()) {
                        s += ",";
                    }
                    s += nl;
                }
                s += getIndent(indentLevel, indentSpaces) + "}";
                return s;
            } else {
                return "";
            }
        }, value.getData());
    }

}

#undef CALL_INFO
