#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Array.hpp"
#include "exqudens/log/util/json/Object.hpp"

namespace exqudens::log::util::json {

    class EXQUDENS_LOG_API_EXPORT Value {

        private:

            std::variant<std::nullptr_t, bool, long double, intmax_t, std::string, Array, Object> data;

        public:

            Value& setNull();

            Value& setBoolean(bool value);

            Value& setNumber(long double value);

            Value& setInteger(intmax_t value);

            Value& setString(const std::string& value);

            Value& setArray(const Array& value);

            Value& setObject(const Object& value);

            bool isNull() const;

            bool isBoolean() const;

            bool isNumber() const;

            bool isInteger() const;

            bool isString() const;

            bool isArray() const;

            bool isObject() const;

            std::nullptr_t getNull() const;

            bool getBoolean() const;

            long double getNumber() const;

            intmax_t getInteger() const;

            std::string getString() const;

            Array getArray() const;

            Object getObject() const;

            std::variant<std::nullptr_t, bool, long double, intmax_t, std::string, Array, Object> getData() const;

            bool operator==(const Value& other) const;

            bool operator!=(const Value& other) const;
    };
}

// implementation ---

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE Value& Value::setNull() {
        data = nullptr;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setBoolean(bool value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setNumber(long double value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setInteger(intmax_t value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setString(const std::string& value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setArray(const Array& value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE Value& Value::setObject(const Object& value) {
        data = value;
        return *this;
    }

    EXQUDENS_LOG_INLINE bool Value::isNull() const {
        return std::holds_alternative<std::nullptr_t>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isBoolean() const {
        return std::holds_alternative<bool>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isNumber() const {
        return std::holds_alternative<long double>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isInteger() const {
        return std::holds_alternative<intmax_t>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isString() const {
        return std::holds_alternative<std::string>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isArray() const {
        return std::holds_alternative<Array>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::isObject() const {
        return std::holds_alternative<Object>(data);
    }

    EXQUDENS_LOG_INLINE std::nullptr_t Value::getNull() const {
        return std::get<std::nullptr_t>(data);
    }

    EXQUDENS_LOG_INLINE bool Value::getBoolean() const {
        return std::get<bool>(data);
    }

    EXQUDENS_LOG_INLINE long double Value::getNumber() const {
        return std::get<long double>(data);
    }

    EXQUDENS_LOG_INLINE intmax_t Value::getInteger() const {
        return std::get<intmax_t>(data);
    }

    EXQUDENS_LOG_INLINE std::string Value::getString() const {
        return std::get<std::string>(data);
    }

    EXQUDENS_LOG_INLINE Array Value::getArray() const {
        return std::get<Array>(data);
    }

    EXQUDENS_LOG_INLINE Object Value::getObject() const {
        return std::get<Object>(data);
    }

    EXQUDENS_LOG_INLINE std::variant<std::nullptr_t, bool, long double, intmax_t, std::string, Array, Object> Value::getData() const {
        return data;
    }

    EXQUDENS_LOG_INLINE bool Value::operator==(const Value& other) const = default;

    EXQUDENS_LOG_INLINE bool Value::operator!=(const Value& other) const = default;
}
