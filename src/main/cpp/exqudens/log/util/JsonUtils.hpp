/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Parser.hpp"
#include "exqudens/log/model/Configuration.hpp"
#include "exqudens/log/model/Constant.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT JsonUtils {

        public:

            JsonUtils() = delete;

            ~JsonUtils() = delete;

            static std::map<std::string, std::string> toMapStringString(const std::string& value);

            static exqudens::log::model::Configuration toConfiguration(const std::string& value);

        private:

            static std::string join(const std::vector<std::string>& part1 = {}, const std::vector<std::string>& part2 = {}, const std::string& delimiter = ".");

            static std::vector<std::string> add(const std::vector<std::string>& part1 = {}, const std::vector<std::string>& part2 = {});

            static json::Value parse(const std::string& stringValue);

            static exqudens::log::model::Configuration toConfiguration(const json::Value& jsonValue);

            static exqudens::log::model::FormatterConfiguration toFormatterConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys,
                const std::set<std::string>& validKeys
            );

            static exqudens::log::model::FormatterConfiguration::Parameter toFormatterConfigurationParameter(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys,
                const std::set<std::string>& validKeys
            );

            static exqudens::log::model::HandlerConfiguration toHandlerConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys
            );

            static exqudens::log::model::LoggerConfiguration toLoggerConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys
            );

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <numeric>

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::map<std::string, std::string> JsonUtils::toMapStringString(const std::string& value) {
        try {
            json::Value jsonValue = parse(value);

            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": json value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();
            std::map<std::string, std::string> result = {};

            for (const auto& jsonObjectPair : jsonObject) {

                if (!jsonObjectPair.second.is_string()) {
                    throw std::runtime_error(CALL_INFO + ": json '" + jsonObjectPair.first + "' value is not a string!");
                }

                result[jsonObjectPair.first] = jsonObjectPair.second.get<std::string>();
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration JsonUtils::toConfiguration(const std::string& value) {
        try {
            json::Value valueJson = parse(value);
            exqudens::log::model::Configuration result = toConfiguration(valueJson);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::string JsonUtils::join(const std::vector<std::string>& part1, const std::vector<std::string>& part2, const std::string& delimiter) {
        try {
            std::string result;
            if (!part1.empty()) {
                result = std::accumulate(
                        part1.begin(),
                        part1.end(),
                        std::string(),
                        [&delimiter](const std::string& a, const std::string& b) {
                            return a + (a.empty() ? "" : delimiter) + b;
                        }
                );
            }
            if (!part2.empty()) {
                result += delimiter;
                result += std::accumulate(
                        part2.begin(),
                        part2.end(),
                        std::string(),
                        [&delimiter](const std::string& a, const std::string& b) {
                            return a + (a.empty() ? "" : delimiter) + b;
                        }
                );
            }
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE std::vector<std::string> JsonUtils::add(const std::vector<std::string>& part1, const std::vector<std::string>& part2) {
        try {
            std::vector<std::string> result = part1;
            result.insert(result.end(), part2.begin(), part2.end());
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE json::Value JsonUtils::parse(const std::string& stringValue) {
        try {
            json::Parser parser(stringValue);
            json::Value result = parser.parse();
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration JsonUtils::toConfiguration(const json::Value& jsonValue) {
        try {
            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": json value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();
            exqudens::log::model::Configuration result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("formatters") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_object()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + jsonObjectPair.first + "' value is not an object!");
                    }
                    json::Object formattersJsonObject = jsonObjectPair.second.get<json::Object>();
                    for (const auto& formattersJsonObjectPair : formattersJsonObject) {
                        auto formatter = toFormatterConfiguration(
                            formattersJsonObjectPair.second,
                            {jsonObjectPair.first, formattersJsonObjectPair.first},
                            exqudens::log::model::Constant::FORMATTER_PARAMETER_IDS
                        );
                        formatter.id = formattersJsonObjectPair.first;
                        result.formatters[formatter.id] = formatter;
                    }
                } else if (std::string("handlers") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_object()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + jsonObjectPair.first + "' value is not an object!");
                    }
                    json::Object handlersJsonObject = jsonObjectPair.second.get<json::Object>();
                    for (const auto& handlersJsonObjectPair : handlersJsonObject) {
                        auto handler = toHandlerConfiguration(
                            handlersJsonObjectPair.second,
                            {jsonObjectPair.first, handlersJsonObjectPair.first}
                        );
                        handler.id = handlersJsonObjectPair.first;
                        result.handlers[handler.id] = handler;
                    }
                } else if (std::string("loggers") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_object()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + jsonObjectPair.first + "' value is not an object!");
                    }
                    json::Object loggersJsonObject = jsonObjectPair.second.get<json::Object>();
                    for (const auto& loggersJsonObjectPair : loggersJsonObject) {
                        auto logger = toLoggerConfiguration(
                            loggersJsonObjectPair.second,
                            {jsonObjectPair.first, loggersJsonObjectPair.first}
                        );
                        logger.id = loggersJsonObjectPair.first;
                        result.loggers[logger.id] = logger;
                    }
                } else {
                    throw std::runtime_error(CALL_INFO + ": json unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::FormatterConfiguration JsonUtils::toFormatterConfiguration(
        const json::Value& jsonValue,
        const std::vector<std::string>& parentKeys,
        const std::set<std::string>& validKeys
    ) {
        try {
            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": 'exqudens::log::model::FormatterConfiguration' json value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();
            exqudens::log::model::FormatterConfiguration result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("format") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_string()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                    }
                    result.format = jsonObjectPair.second.get<std::string>();
                } else if (std::string("parameters") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_object()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not an object!");
                    }
                    json::Object parametersJsonObject = jsonObjectPair.second.get<json::Object>();
                    for (const auto& parametersJsonObjectPair : parametersJsonObject) {
                        if (!validKeys.contains(parametersJsonObjectPair.first)) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' unexpected key: '" + parametersJsonObjectPair.first + "'!");
                        }
                        std::set<std::string> parameterValidKeys = {};
                        if (parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP) {
                            parameterValidKeys.insert("format");
                            parameterValidKeys.insert("seconds");
                            parameterValidKeys.insert("size");
                            parameterValidKeys.insert("reverse");
                        } else if (parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LEVEL) {
                            parameterValidKeys.insert("name");
                            parameterValidKeys.insert("size");
                            parameterValidKeys.insert("reverse");
                        } else if (
                            parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_THREAD
                            || parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LOGGER
                            || parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FUNCTION
                            || parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LINE
                            || parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_MESSAGE
                        ) {
                            parameterValidKeys.insert("size");
                            parameterValidKeys.insert("reverse");
                        } else if (parametersJsonObjectPair.first == exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FILE) {
                            parameterValidKeys.insert("base");
                            parameterValidKeys.insert("name");
                            parameterValidKeys.insert("size");
                            parameterValidKeys.insert("reverse");
                        }
                        auto parameter = toFormatterConfigurationParameter(
                            parametersJsonObjectPair.second,
                            add(parentKeys, {jsonObjectPair.first, parametersJsonObjectPair.first}),
                            parameterValidKeys
                        );
                        parameter.id = parametersJsonObjectPair.first;
                        result.parameters[parameter.id] = parameter;
                    }
                } else {
                    throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::FormatterConfiguration::Parameter JsonUtils::toFormatterConfigurationParameter(
        const json::Value& jsonValue,
        const std::vector<std::string>& parentKeys,
        const std::set<std::string>& validKeys
    ) {
        try {
            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();
            exqudens::log::model::FormatterConfiguration::Parameter result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (validKeys.contains(jsonObjectPair.first)) {
                    if (std::string("format") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_string()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                        }
                        result.format = jsonObjectPair.second.get<std::string>();
                    } else if (std::string("seconds") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_number()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a number!");
                        }
                        result.seconds = static_cast<uint16_t>(jsonObjectPair.second.get<double>());
                    } else if (std::string("size") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_number()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a number!");
                        }
                        result.seconds = static_cast<size_t>(jsonObjectPair.second.get<double>());
                    } else if (std::string("reverse") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_bool()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a bool!");
                        }
                        result.name = jsonObjectPair.second.get<bool>();
                    } else if (std::string("name") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_bool()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a bool!");
                        }
                        result.name = jsonObjectPair.second.get<bool>();
                    } else if (std::string("base") == jsonObjectPair.first) {
                        if (!jsonObjectPair.second.is_string()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                        }
                        result.base = jsonObjectPair.second.get<std::string>();
                    }
                } else {
                    throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::HandlerConfiguration JsonUtils::toHandlerConfiguration(
        const json::Value& jsonValue,
        const std::vector<std::string>& parentKeys
    ) {
        try {
            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();

            if (!jsonObject.contains("formatter")) {
                throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' value missing key: 'formatter'!");
            }

            exqudens::log::model::HandlerConfiguration result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("type") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_string()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                    }
                    result.type = jsonObjectPair.second.get<std::string>();
                } else if (std::string("stream") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_string()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                    }
                    result.stream = jsonObjectPair.second.get<std::string>();
                } else if (std::string("file") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_string()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                    }
                    result.file = jsonObjectPair.second.get<std::string>();
                } else if (std::string("size") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_number()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a number!");
                    }
                    result.size = static_cast<size_t>(jsonObjectPair.second.get<double>());
                } else if (std::string("formatter") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_string()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a string!");
                    }
                    result.formatter = jsonObjectPair.second.get<std::string>();
                } else {
                    throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::LoggerConfiguration JsonUtils::toLoggerConfiguration(
        const json::Value& jsonValue,
        const std::vector<std::string>& parentKeys
    ) {
        try {
            if (!jsonValue.is_object()) {
                throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' value is not an object!");
            }

            json::Object jsonObject = jsonValue.get<json::Object>();
            exqudens::log::model::LoggerConfiguration result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("level") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_number()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not a number!");
                    }
                    result.level = static_cast<uint16_t>(jsonObjectPair.second.get<double>());
                } else if (std::string("handlers") == jsonObjectPair.first) {
                    if (!jsonObjectPair.second.is_array()) {
                        throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first}) + "' value is not an array!");
                    }
                    std::vector<std::string> handlers = {};
                    json::Array jsonArray = jsonObjectPair.second.get<json::Array>();
                    for (size_t i = 0; i < jsonArray.size(); i++) {
                        if (!jsonArray.at(i).is_string()) {
                            throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys, {jsonObjectPair.first, std::to_string(i)}) + "' value is not a string!");
                        }
                        std::string handler = jsonArray.at(i).get<std::string>();
                        handlers.emplace_back(handler);
                    }
                    result.handlers = handlers;
                } else {
                    throw std::runtime_error(CALL_INFO + ": json '" + join(parentKeys) + "' unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
