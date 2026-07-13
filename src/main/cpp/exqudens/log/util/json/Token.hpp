#pragma once

#include <string>

#include "exqudens/log/util/json/TokenType.hpp"

namespace exqudens::log::util::json {

    struct Token {
        TokenType type;
        std::string value;
    };
}
