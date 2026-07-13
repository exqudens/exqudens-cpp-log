#pragma once

namespace exqudens::log::util::json {

    enum class TokenType {
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
}
