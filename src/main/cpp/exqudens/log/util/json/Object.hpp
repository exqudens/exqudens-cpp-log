#pragma once

#include <string>
#include <map>

#include "exqudens/log/export.hpp"

namespace exqudens::log::util::json {

    struct Value;

    class EXQUDENS_LOG_API_EXPORT Object : public std::map<std::string, Value> {

        public:

            using std::map<std::string, Value>::map;

            Object& add(const std::string& key, const Value& value);

    };
}

// implementation ---

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE Object& Object::add(const std::string& key, const Value& value) {
        insert_or_assign(key, value);
        return *this;
    }

}
