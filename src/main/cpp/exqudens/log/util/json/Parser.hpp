#pragma once

#include <string>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Token.hpp"
#include "exqudens/log/util/json/Value.hpp"
#include "exqudens/log/util/json/Lexer.hpp"

namespace exqudens::log::util::json {

    class EXQUDENS_LOG_API_EXPORT Parser {

        private:

            Lexer lexer;
            Token current;

        public:

            explicit Parser(const std::string& source);

            Value parse();

        private:

            void consume(Token::Type type);
    };
}

// implementation ---

#include <cstddef>
#include <filesystem>
#include <utility>
#include <stdexcept>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE Parser::Parser(const std::string& source): lexer(source) {
        current = lexer.next_token();
    }

    EXQUDENS_LOG_INLINE Value Parser::parse() {
        Value node;
        if (current.type == Token::Type::ObjectOpen) {
            consume(Token::Type::ObjectOpen);
            Object obj;
            if (current.type != Token::Type::ObjectClose) {
                while (true) {
                    if (current.type != Token::Type::String) {
                        throw std::runtime_error(CALL_INFO + ": Key must be string");
                    }
                    std::string key = current.value;
                    consume(Token::Type::String);
                    consume(Token::Type::Colon);
                    obj[key] = parse();
                    if (current.type == Token::Type::Comma) {
                        consume(Token::Type::Comma);
                    } else {
                        break;
                    }
                }
            }
            consume(Token::Type::ObjectClose);
            node.setObject(obj);
        } else if (current.type == Token::Type::ArrayOpen) {
            consume(Token::Type::ArrayOpen);
            Array arr;
            if (current.type != Token::Type::ArrayClose) {
                while (true) {
                    arr.push_back(parse());
                    if (current.type == Token::Type::Comma) {
                        consume(Token::Type::Comma);
                    } else {
                        break;
                    }
                }
            }
            consume(Token::Type::ArrayClose);
            node.setArray(arr);
        } else if (current.type == Token::Type::String) {
            node.setString(current.value);
            consume(Token::Type::String);
        } else if (current.type == Token::Type::Number) {
            size_t indexOfDot = current.value.find('.');
            if (indexOfDot == std::string::npos) {
                node.setInteger(std::stoll(current.value));
            } else {
                if (current.value.find_first_not_of('0', indexOfDot + 1) == std::string::npos) {
                    node.setInteger(std::stoll(current.value));
                } else {
                    node.setNumber(std::stold(current.value));
                }
            }
            consume(Token::Type::Number);
        } else if (current.type == Token::Type::True) {
            node.setBoolean(true);
            consume(Token::Type::True);
        } else if (current.type == Token::Type::False) {
            node.setBoolean(false);
            consume(Token::Type::False);
        } else if (current.type == Token::Type::Null) {
            node.setNull();
            consume(Token::Type::Null);
        } else {
            throw std::runtime_error("Invalid token parsing stream");
        }
        return node;
    }

    EXQUDENS_LOG_INLINE void Parser::consume(Token::Type type) {
        if (current.type != type) {
            throw std::runtime_error("Unexpected syntax match error");
        }
        current = lexer.next_token();
    }
}

#undef CALL_INFO
