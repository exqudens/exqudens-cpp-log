#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>
#include <cctype>

namespace exqudens::log::util::json {

    struct Value;

    using Object = std::map<std::string, Value>;
}
