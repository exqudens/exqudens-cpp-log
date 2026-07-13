#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

#include "exqudens/log/util/json/TokenType.hpp"
#include "exqudens/log/util/json/Token.hpp"
#include "exqudens/log/util/json/Value.hpp"
#include "exqudens/log/util/json/Lexer.hpp"

namespace exqudens::log::util::json {

    class Parser {
    private:
        Lexer lexer;
        Token current;

        void consume(TokenType type) {
            if (current.type != type) throw std::runtime_error("Unexpected syntax match error");
            current = lexer.next_token();
        }

    public:
        explicit Parser(const std::string& source) : lexer(source) {
            current = lexer.next_token();
        }

        Value parse() {
            Value node;
            if (current.type == TokenType::ObjectOpen) {
                consume(TokenType::ObjectOpen);
                Object obj;
                if (current.type != TokenType::ObjectClose) {
                    while (true) {
                        if (current.type != TokenType::String) throw std::runtime_error("Key must be string");
                        std::string key = current.value;
                        consume(TokenType::String);
                        consume(TokenType::Colon);
                        obj[key] = parse();
                        if (current.type == TokenType::Comma) {
                            consume(TokenType::Comma);
                        } else break;
                    }
                }
                consume(TokenType::ObjectClose);
                node.data = obj;
            } else if (current.type == TokenType::ArrayOpen) {
                consume(TokenType::ArrayOpen);
                Array arr;
                if (current.type != TokenType::ArrayClose) {
                    while (true) {
                        arr.push_back(parse());
                        if (current.type == TokenType::Comma) {
                            consume(TokenType::Comma);
                        } else {
                            break;
                        }
                    }
                }
                consume(TokenType::ArrayClose);
                node.data = arr;
            } else if (current.type == TokenType::String) {
                node.data = current.value;
                consume(TokenType::String);
            } else if (current.type == TokenType::Number) {
                node.data = std::stod(current.value);
                consume(TokenType::Number);
            } else if (current.type == TokenType::True) {
                node.data = true;
                consume(TokenType::True);
            } else if (current.type == TokenType::False) {
                node.data = false;
                consume(TokenType::False);
            } else if (current.type == TokenType::Null) {
                node.data = nullptr;
                consume(TokenType::Null);
            } else {
                throw std::runtime_error("Invalid token parsing stream");
            }
            return node;
        }
    };
}
