#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include <string_view>

#include "exqudens/log/util/json/Token.hpp"

namespace exqudens::log::util::json {

    class Lexer {

        private:

            std::string src;
            size_t pos = 0;

            void skip_whitespace() {
                while (pos < src.size() && (src[pos] == ' ' || src[pos] == '\t' || src[pos] == '\n' || src[pos] == '\r')) {
                    pos++;
                }
            }

        public:

            explicit Lexer(std::string source) : src(std::move(source)) {}

            Token next_token() {
                skip_whitespace();
                if (pos >= src.size()) return {TokenType::EndOfFile, ""};

                char c = src[pos];
                if (c == '{') { pos++; return {TokenType::ObjectOpen, "{"}; }
                if (c == '}') { pos++; return {TokenType::ObjectClose, "}"}; }
                if (c == '[') { pos++; return {TokenType::ArrayOpen, "["}; }
                if (c == ']') { pos++; return {TokenType::ArrayClose, "]"}; }
                if (c == ':') { pos++; return {TokenType::Colon, ":"}; }
                if (c == ',') { pos++; return {TokenType::Comma, ","}; }

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

                            switch (escape_type) {
                                case '"':  parsed_str += '"';  break;
                                case '\\': parsed_str += '\\'; break;
                                case '/':  parsed_str += '/';  break;
                                case 'b':  parsed_str += '\b'; break;
                                case 'f':  parsed_str += '\f'; break;
                                case 'n':  parsed_str += '\n'; break;
                                case 'r':  parsed_str += '\r'; break;
                                case 't':  parsed_str += '\t'; break;
                                case 'u': {
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
                                    break;
                                }
                                default:
                                    throw std::runtime_error("Invalid JSON escape control sequence: \\" + std::string(1, escape_type));
                            }
                        }
                        else {
                            parsed_str += current_char;
                            pos++;
                        }
                    }

                    if (!done) {
                        throw std::runtime_error("Unterminated string literal inside JSON file");
                    }

                    return {TokenType::String, parsed_str};
                }

                // Numbers
                if (std::isdigit(c) || c == '-') {
                    size_t start = pos;
                    if (c == '-') pos++;
                    while (pos < src.size() && (std::isdigit(src[pos]) || src[pos] == '.')) pos++;
                    return {TokenType::Number, src.substr(start, pos - start)};
                }

                // Literals (true, false, null)
                if (src.compare(pos, 4, "true") == 0)  { pos += 4; return {TokenType::True, "true"}; }
                if (src.compare(pos, 5, "false") == 0) { pos += 5; return {TokenType::False, "false"}; }
                if (src.compare(pos, 4, "null") == 0)  { pos += 4; return {TokenType::Null, "null"}; }

                throw std::runtime_error("Unexpected token lookahead character: " + std::string(1, c));
            }
    };
}
