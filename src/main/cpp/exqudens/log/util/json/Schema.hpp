#pragma once

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Value.hpp"

namespace exqudens::log::util::json {

    class EXQUDENS_LOG_API_EXPORT Schema {

        public:

            static bool validate(const Value& schema, const Value& value, std::string& errorMessage);

            static bool validate(const Value& schema, const Value& value);

            static bool validate(const Value& schema, std::string& errorMessage, bool recursive = true);

            static bool validate(const Value& schema);
    };
}

// implementation ---

#include <cstddef>
#include <string>
#include <filesystem>
#include <limits>
#include <stdexcept>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util::json {

    EXQUDENS_LOG_INLINE bool Schema::validate(const Value& schema, const Value& value, std::string& errorMessage) {
        // 1. Validate Type
        if (!validate(schema, errorMessage, false)) {
            return false;
        }
        if (schema.getObject().contains("type")) {
            std::string type = schema.getObject().at("type").getString();
            if (type == "object" && !value.isObject()) { errorMessage = "Expected 'object'"; return false; }
            if (type == "array" && !value.isArray()) { errorMessage = "Expected 'array'"; return false; }
            if (type == "string" && !value.isString()) { errorMessage = "Expected 'string'"; return false; }
            if (type == "number" && !value.isNumber()) { errorMessage = "Expected 'number'"; return false; }
            if (type == "integer" && !value.isInteger()) { errorMessage = "Expected 'integer'"; return false; }
            if (type == "boolean" && !value.isBoolean()) { errorMessage = "Expected 'boolean'"; return false; }
        }

        // 2. Validate Object Properties
        if (value.isObject()) {

            const auto& valueObject = value.getObject();

            // Check for required fields first
            if (schema.getObject().contains("required")) {
                const auto& required = schema.getObject().at("required").getArray();

                for (size_t i = 0; i < required.size(); i++) {
                    if (!valueObject.contains(required.at(i).getString())) {
                        errorMessage = "Missing required field '" + required.at(i).getString() + "'";
                        return false;
                    }
                }
            }

            // Check field types according to 'minProperties'
            if (schema.getObject().contains("minProperties")) {
                if (valueObject.size() < schema.getObject().at("minProperties").getInteger()) {
                    errorMessage = "Object size below 'minProperties' constraint: " + std::to_string(schema.getObject().at("minProperties").getInteger());
                    return false;
                }
            }

            // Check field types according to 'maxProperties'
            if (schema.getObject().contains("maxProperties")) {
                if (valueObject.size() > schema.getObject().at("maxProperties").getInteger()) {
                    errorMessage = "Object size exceeds 'maxProperties' constraint: " + std::to_string(schema.getObject().at("maxProperties").getInteger());
                    return false;
                }
            }

            // Check field types according to 'properties'
            if (schema.getObject().contains("properties")) {
                const auto& properties = schema.getObject().at("properties").getObject();

                // Validate individual field schemas recursively
                bool additionalPropertiesAllowed = true;
                if (schema.getObject().contains("additionalProperties")) {
                    if (schema.getObject().at("additionalProperties").isBoolean()) {
                        additionalPropertiesAllowed = schema.getObject().at("additionalProperties").getBoolean();
                    } else if (schema.getObject().at("additionalProperties").isObject()) {
                        additionalPropertiesAllowed = true;
                    }
                }
                for (auto& [k, v] : valueObject) {
                    if (properties.contains(k)) {
                        if (!validate(properties.at(k), v, errorMessage)) {
                            errorMessage = "[" + k + "] -> " + errorMessage;
                            return false;
                        }
                    } else {
                        if (additionalPropertiesAllowed) {
                            if (schema.getObject().contains("additionalProperties") && schema.getObject().at("additionalProperties").isObject()) {
                                if (!validate(schema.getObject().at("additionalProperties"), v, errorMessage)) {
                                    errorMessage = "[" + k + "] -> " + errorMessage;
                                    return false;
                                }
                            }
                        } else {
                            if (!errorMessage.empty()) {
                                errorMessage += " ";
                            }
                            errorMessage = errorMessage + "Unallowed field '" + k + "'";
                            return false;
                        }
                    }
                }
            } else {
                // Validate individual field schemas recursively
                bool additionalPropertiesAllowed = true;
                if (schema.getObject().contains("additionalProperties")) {
                    if (schema.getObject().at("additionalProperties").isBoolean()) {
                        additionalPropertiesAllowed = schema.getObject().at("additionalProperties").getBoolean();
                    } else if (schema.getObject().at("additionalProperties").isObject()) {
                        additionalPropertiesAllowed = true;
                    }
                }
                for (auto& [k, v] : valueObject) {
                    if (additionalPropertiesAllowed) {
                        if (schema.getObject().contains("additionalProperties") && schema.getObject().at("additionalProperties").isObject()) {
                            if (!validate(schema.getObject().at("additionalProperties"), v, errorMessage)) {
                                errorMessage = "[" + k + "] -> " + errorMessage;
                                return false;
                            }
                        }
                    } else {
                        if (!errorMessage.empty()) {
                            errorMessage += " ";
                        }
                        errorMessage = errorMessage + "Unallowed field '" + k + "'";
                        return false;
                    }
                }
            }
        }

        // 3. Validate Array
        if (value.isArray()) {
            const auto& valueArray = value.getArray();

            if (schema.getObject().contains("minItems")) {
                if (valueArray.size() < schema.getObject().at("minItems").getInteger()) {
                    errorMessage = "Array size below 'minItems' constraint: " + std::to_string(schema.getObject().at("minItems").getInteger());
                    return false;
                }
            }

            if (schema.getObject().contains("maxItems")) {
                if (valueArray.size() > schema.getObject().at("maxItems").getInteger()) {
                    errorMessage = "Array size exceeds 'maxItems' constraint: " + std::to_string(schema.getObject().at("maxItems").getInteger());
                    return false;
                }
            }

            if (schema.getObject().contains("uniqueItems")) {
                if (schema.getObject().at("uniqueItems").getBoolean()) {
                    for (size_t i = 0; i < valueArray.size(); i++) {
                        for (size_t j = i + 1; j < valueArray.size(); j++) {
                            if (valueArray.at(i) == valueArray.at(j)) {
                                errorMessage = "Array contains duplicates";
                                return false;
                            }
                        }
                    }
                }
            }

            if (schema.getObject().contains("items")) {
                for (size_t i = 0; i < valueArray.size(); i++) {
                    if (!validate(schema.getObject().at("items"), errorMessage)) {
                        errorMessage = "[items] -> " + errorMessage;
                        return false;
                    }
                    if (!validate(schema.getObject().at("items"), valueArray.at(i), errorMessage)) {
                        errorMessage = "[" + std::to_string(i) + "] -> " + errorMessage;
                        return false;
                    }
                }
            }
        }

        // 4. Validate Number Boundaries
        if (value.isNumber()) {
            if (schema.getObject().contains("minimum")) {
                if (schema.getObject().at("minimum").isNumber() && value.getNumber() < schema.getObject().at("minimum").getNumber()) {
                    errorMessage = "Value below 'minimum' constraint: " + std::to_string(schema.getObject().at("minimum").getNumber());
                    return false;
                }
                if (schema.getObject().at("minimum").isInteger() && value.getNumber() < (long double) schema.getObject().at("minimum").getInteger()) {
                    errorMessage = "Value below 'minimum' constraint: " + std::to_string(schema.getObject().at("minimum").getInteger());
                    return false;
                }
            }
            if (schema.getObject().contains("maximum")) {
                if (schema.getObject().at("maximum").isNumber() && value.getNumber() > schema.getObject().at("maximum").getNumber()) {
                    errorMessage = "Value exceeds 'maximum' constraint: " + std::to_string(schema.getObject().at("maximum").getNumber());
                    return false;
                }
                if (schema.getObject().at("maximum").isInteger() && value.getNumber() > (long double) schema.getObject().at("maximum").getInteger()) {
                    errorMessage = "Value exceeds 'maximum' constraint: " + std::to_string(schema.getObject().at("maximum").getInteger());
                    return false;
                }
            }
        }

        // 5. Validate Integer Boundaries
        if (value.isInteger()) {
            if (schema.getObject().contains("minimum")) {
                if (value.getInteger() < schema.getObject().at("minimum").getInteger()) {
                    errorMessage = "Value below 'minimum' constraint: " + std::to_string(schema.getObject().at("minimum").getInteger());
                    return false;
                }
            }
            if (schema.getObject().contains("maximum")) {
                if (value.getInteger() > schema.getObject().at("maximum").getInteger()) {
                    errorMessage = "Value exceeds 'maximum' constraint: " + std::to_string(schema.getObject().at("maximum").getInteger());
                    return false;
                }
            }
        }

        return true;
    }

    EXQUDENS_LOG_INLINE bool Schema::validate(const Value& schema, const Value& value) {
        std::string errorMessage = {};
        bool result = validate(schema, value, errorMessage);
        if (!result) {
            throw std::runtime_error(CALL_INFO + ": " + errorMessage);
        }
        return result;
    }

    EXQUDENS_LOG_INLINE bool Schema::validate(const Value& schema, std::string& errorMessage, bool recursive) {
        // 1. Validate 'type'
        if (!schema.isObject()) {
            errorMessage = "Schema expected 'object'";
            return false;
        }
        if (schema.getObject().contains("type")) {
            if (!schema.getObject().at("type").isString()) {
                errorMessage = "Schema 'type' expected 'string'";
                return false;
            }
            std::string type = schema.getObject().at("type").getString();
            if (
                type != "object"
                && type != "array"
                && type != "string"
                && type != "number"
                && type != "integer"
                && type != "boolean"
            ) {
                errorMessage = "Schema 'type' expected 'object' or 'array' or 'string' or 'number' or 'integer' or 'boolean'";
                return false;
            }
        }

        // 2.1. Validate Object Check for 'required' fields first
        if (schema.getObject().contains("required")) {
            if (!schema.getObject().at("required").isArray()) {
                errorMessage = "Schema 'required' expected 'array'";
                return false;
            }

            const auto& required = schema.getObject().at("required").getArray();

            for (size_t i = 0; i < required.size(); i++) {
                if (!required.at(i).isString()) {
                    errorMessage = "Schema 'required' ";
                    errorMessage += std::to_string(i);
                    errorMessage += " expected 'string'";
                    return false;
                }
            }
        }

        // 2.2. Validate Object Check field types according to 'minProperties'
        if (schema.getObject().contains("minProperties")) {
            if (!schema.getObject().at("minProperties").isInteger()) {
                errorMessage = "Schema 'minProperties' expected 'integer'";
                return false;
            }
            if (schema.getObject().at("minProperties").getInteger() < 0) {
                errorMessage = "Schema 'minProperties' expected positive 'integer'";
                return false;
            }
            if (schema.getObject().at("minProperties").getInteger() > std::numeric_limits<std::intmax_t>::max()) {
                errorMessage = "Schema 'minProperties' exceeds maximum 'integer'";
                return false;
            }
        }

        // 2.3. Validate Object Check field types according to 'maxProperties'
        if (schema.getObject().contains("maxProperties")) {
            if (!schema.getObject().at("maxProperties").isInteger()) {
                errorMessage = "Schema 'maxProperties' expected 'integer'";
                return false;
            }
            if (schema.getObject().at("maxProperties").getInteger() < 0) {
                errorMessage = "Schema 'maxProperties' expected positive 'integer'";
                return false;
            }
            if (schema.getObject().at("maxProperties").getInteger() > std::numeric_limits<std::intmax_t>::max()) {
                errorMessage = "Schema 'maxProperties' exceeds maximum 'integer'";
                return false;
            }
        }

        // 2.4. Validate Object Check field types according to 'properties'
        if (schema.getObject().contains("properties")) {
            if (!schema.getObject().at("properties").isObject()) {
                errorMessage = "Schema 'properties' expected 'object'";
                return false;
            }

            const auto& properties = schema.getObject().at("properties").getObject();

            if (recursive) {
                // Validate individual field schemas recursively
                for (auto& [k, v] : properties) {
                    if (!validate(v, errorMessage, recursive)) {
                        errorMessage = "[" + k + "] -> " + errorMessage;
                        return false;
                    }
                }
            }
        }

        // 2.5. Validate Object Check field types according to 'additionalProperties'
        if (schema.getObject().contains("additionalProperties")) {
            if (
                !schema.getObject().at("additionalProperties").isBoolean()
                && !schema.getObject().at("additionalProperties").isObject()
            ) {
                errorMessage = "Schema 'additionalProperties' expected 'boolean' or 'object'";
                return false;
            }
        }

        // 3.1. Validate Array 'minItems'
        if (schema.getObject().contains("minItems")) {
            if (!schema.getObject().at("minItems").isInteger()) {
                errorMessage = "Schema 'minItems' expected 'integer'";
                return false;
            }
            if (schema.getObject().at("minItems").getInteger() < 0) {
                errorMessage = "Schema 'minItems' expected positive 'integer'";
                return false;
            }
            if (schema.getObject().at("minItems").getInteger() > std::numeric_limits<std::intmax_t>::max()) {
                errorMessage = "Schema 'minItems' exceeds maximum 'integer'";
                return false;
            }
        }

        // 3.2. Validate Array 'maxItems'
        if (schema.getObject().contains("maxItems")) {
            if (!schema.getObject().at("maxItems").isInteger()) {
                errorMessage = "Schema 'minItems' expected 'integer'";
                return false;
            }
            if (schema.getObject().at("maxItems").getInteger() < 0) {
                errorMessage = "Schema 'maxItems' expected positive 'integer'";
                return false;
            }
            if (schema.getObject().at("maxItems").getInteger() > std::numeric_limits<std::intmax_t>::max()) {
                errorMessage = "Schema 'maxItems' exceeds maximum 'integer'";
                return false;
            }
        }

        // 3.3. Validate Array 'uniqueItems'
        if (schema.getObject().contains("uniqueItems")) {
            if (!schema.getObject().at("uniqueItems").isBoolean()) {
                errorMessage = "Schema 'minItems' expected 'boolean'";
                return false;
            }
        }

        // 3.4. Validate Array 'items'
        if (schema.getObject().contains("items")) {
            if (!schema.getObject().at("items").isObject()) {
                errorMessage = "Schema 'items' expected 'object'";
                return false;
            }

            if (recursive) {
                if (!validate(schema.getObject().at("items"), errorMessage, recursive)) {
                    errorMessage = "[items] -> " + errorMessage;
                    return false;
                }
            }
        }

        // 5.1. Validate Number Boundaries 'minimum'
        if (schema.getObject().contains("minimum")) {
            if (!schema.getObject().at("minimum").isNumber() && !schema.getObject().at("minimum").isInteger()) {
                errorMessage = "Schema 'minimum' expected 'number' or 'integer'";
                return false;
            }
        }

        // 5.2. Validate Number Boundaries 'maximum'
        if (schema.getObject().contains("maximum")) {
            if (!schema.getObject().at("maximum").isNumber() && !schema.getObject().at("maximum").isInteger()) {
                errorMessage = "Schema 'maximum' expected 'number' or 'integer'";
                return false;
            }
        }

        // 6.1. Validate Integer Boundaries 'minimum'
        if (schema.getObject().contains("minimum")) {
            if (!schema.getObject().at("minimum").isInteger()) {
                errorMessage = "Schema 'minimum' expected 'integer'";
                return false;
            }
        }

        // 6.2. Validate Integer Boundaries 'maximum'
        if (schema.getObject().contains("maximum")) {
            if (!schema.getObject().at("maximum").isInteger()) {
                errorMessage = "Schema 'maximum' expected 'integer'";
                return false;
            }
        }

        // 7. Validate Number Boundaries 'minimum' less 'maximum'
        if (schema.getObject().contains("minimum") && schema.getObject().contains("maximum")) {
            if (
                schema.getObject().at("minimum").isNumber()
                && schema.getObject().at("maximum").isNumber()
                &&  schema.getObject().at("minimum").getNumber() > schema.getObject().at("maximum").getNumber()
            ) {
                errorMessage = "Schema 'minimum' exceeds 'maximum'";
                return false;
            }

            if (
                schema.getObject().at("minimum").isInteger()
                && schema.getObject().at("maximum").isInteger()
                &&  schema.getObject().at("minimum").getInteger() > schema.getObject().at("maximum").getInteger()
            ) {
                errorMessage = "Schema 'minimum' exceeds 'maximum'";
                return false;
            }

            if (
                schema.getObject().at("minimum").isNumber()
                && schema.getObject().at("maximum").isInteger()
                &&  schema.getObject().at("minimum").getNumber() > schema.getObject().at("maximum").getInteger()
            ) {
                errorMessage = "Schema 'minimum' exceeds 'maximum'";
                return false;
            }

            if (
                schema.getObject().at("minimum").isInteger()
                && schema.getObject().at("maximum").isNull()
                &&  schema.getObject().at("minimum").getInteger() > schema.getObject().at("maximum").getNumber()
            ) {
                errorMessage = "Schema 'minimum' exceeds 'maximum'";
                return false;
            }
        }

        return true;
    }

    EXQUDENS_LOG_INLINE bool Schema::validate(const Value& schema) {
        std::string errorMessage = {};
        bool result = validate(schema, errorMessage);
        if (!result) {
            throw std::runtime_error(CALL_INFO + ": " + errorMessage);
        }
        return result;
    }

}

#undef CALL_INFO
