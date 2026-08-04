#pragma once

#include <vector>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util::json {

    struct Value;

    class EXQUDENS_LOG_API_EXPORT Array : public std::vector<Value> {

        public:

            using std::vector<Value>::vector;

            Array& add(const Value& value);

    };
}

// implementation ---

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE Array& Array::add(const Value& value) {
        emplace_back(value);
        return *this;
    }

}
