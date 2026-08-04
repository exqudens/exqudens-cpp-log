#pragma once

#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util::json {

    struct EXQUDENS_LOG_API_EXPORT Token {

        enum class EXQUDENS_LOG_API_EXPORT Type {
            ObjectOpen,
            ObjectClose,
            ArrayOpen,
            ArrayClose,
            Colon,
            Comma,
            String,
            Number,
            True,
            False,
            Null,
            EndOfFile
        };

        Type type;
        std::string value;
    };
}
