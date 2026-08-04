#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Token.hpp"

namespace exqudens::log::util::json {

    class EXQUDENS_LOG_API_EXPORT Lexer {

        private:

            std::string src = {};
            size_t pos = 0;

        public:

            explicit Lexer(std::string source);

            Token next_token();

        private:

            void skip_whitespace();
    };
}

// implementation ---

#include <filesystem>
#include <utility>
#include <stdexcept>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE Lexer::Lexer(std::string source): src(std::move(source)) {
    }

    EXQUDENS_LOG_INLINE Token Lexer::next_token() {
        skip_whitespace();
        if (pos >= src.size()) return {Token::Type::EndOfFile, ""};

        char c = src[pos];
        if (c == '{') { pos++; return {Token::Type::ObjectOpen, "{"}; }
        if (c == '}') { pos++; return {Token::Type::ObjectClose, "}"}; }
        if (c == '[') { pos++; return {Token::Type::ArrayOpen, "["}; }
        if (c == ']') { pos++; return {Token::Type::ArrayClose, "]"}; }
        if (c == ':') { pos++; return {Token::Type::Colon, ":"}; }
        if (c == ',') { pos++; return {Token::Type::Comma, ","}; }

        // Strings with Escape Sequence Resolution
        if (c == '"') {
            pos++; // Step past the opening quote
            std::string parsed_str;
            bool done = false;

            while (pos < src.size() && !done) {
                char current_char = src[pos];

                if (current_char == '"') {
                    done = true;
                    pos++; // Consume closing quote
                } else if (current_char == '\\') {
                    if (pos + 1 >= src.size()) {
                        throw std::runtime_error("Dangling backslash escape character at end of file");
                    }

                    char escape_type = src[pos + 1];
                    pos += 2; // Advance past both '\' and the escape specifier

                    if (escape_type == '"') {
                        parsed_str += '"';
                    } else if (escape_type == '\\') {
                        parsed_str += '\\';
                    } else if (escape_type == '/') {
                        parsed_str += '/';
                    } else if (escape_type == 'b') {
                        parsed_str += '\b';
                    } else if (escape_type == 'f') {
                        parsed_str += '\f';
                    } else if (escape_type == 'n') {
                        parsed_str += '\n';
                    } else if (escape_type == 'r') {
                        parsed_str += '\r';
                    } else if (escape_type == 't') {
                        parsed_str += '\t';
                    } else if (escape_type == 'u') {
                        // Handle 4-digit hexadecimal unicode tokens (\u0020)
                        if (pos + 4 > src.size()) {
                            throw std::runtime_error("Incomplete hex sequence in string");
                        }
                        std::string hex_str = src.substr(pos, 4);
                        pos += 4;

                        // Convert hex value string to an integer
                        unsigned long codepoint = std::stoul(hex_str, nullptr, 16);

                        // Simple ASCII/UTF-8 conversion for basic characters
                        if (codepoint <= 0x7F) {
                            parsed_str += static_cast<char>(codepoint);
                        } else {
                            // Multi-byte UTF-8 encoding support
                            if (codepoint <= 0x7FF) {
                                parsed_str += static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F));
                                parsed_str += static_cast<char>(0x80 | (codepoint & 0x3F));
                            } else {
                                parsed_str += static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F));
                                parsed_str += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
                                parsed_str += static_cast<char>(0x80 | (codepoint & 0x3F));
                            }
                        }
                    } else {
                        throw std::runtime_error("Invalid JSON escape control sequence: \\" + std::string(1, escape_type));
                    }
                } else {
                    parsed_str += current_char;
                    pos++;
                }
            }

            if (!done) {
                throw std::runtime_error(CALL_INFO + ": Unterminated string literal inside JSON file");
            }

            return {Token::Type::String, parsed_str};
        }

        // Numbers
        if (std::isdigit(c) || c == '-') {
            size_t start = pos;
            if (c == '-') pos++;
            while (pos < src.size() && (std::isdigit(src[pos]) || src[pos] == '.')) pos++;
            return {Token::Type::Number, src.substr(start, pos - start)};
        }

        // Literals (true, false, null)
        if (src.compare(pos, 4, "true") == 0) {
            pos += 4; return {Token::Type::True, "true"};
        }
        if (src.compare(pos, 5, "false") == 0) {
            pos += 5; return {Token::Type::False, "false"};
        }
        if (src.compare(pos, 4, "null") == 0) {
            pos += 4; return {Token::Type::Null, "null"};
        }

        throw std::runtime_error(CALL_INFO + ": Unexpected token lookahead character: " + std::string(1, c));
    }

    EXQUDENS_LOG_INLINE void Lexer::skip_whitespace() {
        while (pos < src.size() && (src[pos] == ' ' || src[pos] == '\t' || src[pos] == '\n' || src[pos] == '\r')) {
            pos++;
        }
    }
}

#undef CALL_INFO
