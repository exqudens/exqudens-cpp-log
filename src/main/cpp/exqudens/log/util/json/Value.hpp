#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>

#include "exqudens/log/util/json/Array.hpp"
#include "exqudens/log/util/json/Object.hpp"

namespace exqudens::log::util::json {

    struct Value {
        std::variant<std::nullptr_t, bool, double, std::string, Array, Object> data;

        // Helper checkers
        bool is_null()   const { return std::holds_alternative<std::nullptr_t>(data); }
        bool is_bool()   const { return std::holds_alternative<bool>(data); }
        bool is_number() const { return std::holds_alternative<double>(data); }
        bool is_string() const { return std::holds_alternative<std::string>(data); }
        bool is_array()  const { return std::holds_alternative<Array>(data); }
        bool is_object() const { return std::holds_alternative<Object>(data); }

        // Direct accessors
        template<typename T> const T& get() const { return std::get<T>(data); }
    };
}
