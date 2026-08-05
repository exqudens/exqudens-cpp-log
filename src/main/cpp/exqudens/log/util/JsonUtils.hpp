/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <string>
#include <optional>
#include <vector>
#include <set>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/util/json/Value.hpp"
#include "exqudens/log/model/Configuration.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_API_EXPORT JsonUtils {

        private:

            inline static const json::Value configurationSchema = json::Value().setObject(
                json::Object()
                .add("type", json::Value().setString("object"))
                .add("required", json::Value().setArray(
                    json::Array()
                    .add(json::Value().setString("formatters"))
                    .add(json::Value().setString("handlers"))
                    .add(json::Value().setString("loggers"))
                ))
                .add("properties", json::Value().setObject(
                    json::Object()
                    .add("formatters", json::Value().setObject(
                        json::Object()
                        .add("type", json::Value().setString("object"))
                        .add("minProperties", json::Value().setInteger(1))
                        .add("additionalProperties", json::Value().setObject(
                            json::Object()
                            .add("type", json::Value().setString("object"))
                            .add("required", json::Value().setArray(
                                json::Array()
                                .add(json::Value().setString("format"))
                            ))
                            .add("properties", json::Value().setObject(
                                json::Object()
                                .add("format", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("string"))
                                ))
                                .add("parameters", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("object"))
                                    .add("minProperties", json::Value().setInteger(1))
                                    .add("properties", json::Value().setObject(
                                        json::Object()
                                        .add("timestamp", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("format", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("string"))
                                                ))
                                                .add("seconds", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                    .add("maximum", json::Value().setInteger(8))
                                                ))
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("level", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("name", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("thread", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("logger", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("function", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("file", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("base", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("string"))
                                                ))
                                                .add("name", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("line", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                        .add("message", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("object"))
                                            .add("properties", json::Value().setObject(
                                                json::Object()
                                                .add("size", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("integer"))
                                                    .add("minimum", json::Value().setInteger(1))
                                                ))
                                                .add("reverse", json::Value().setObject(
                                                    json::Object()
                                                    .add("type", json::Value().setString("boolean"))
                                                ))
                                            ))
                                            .add("additionalProperties", json::Value().setBoolean(false))
                                        ))
                                    ))
                                    .add("additionalProperties", json::Value().setBoolean(false))
                                ))
                            ))
                            .add("additionalProperties", json::Value().setBoolean(false))
                        ))
                    ))
                    .add("handlers", json::Value().setObject(
                        json::Object()
                        .add("type", json::Value().setString("object"))
                        .add("minProperties", json::Value().setInteger(1))
                        .add("additionalProperties", json::Value().setObject(
                            json::Object()
                            .add("type", json::Value().setString("object"))
                            .add("required", json::Value().setArray(
                                json::Array()
                                .add(json::Value().setString("type"))
                                .add(json::Value().setString("formatter"))
                            ))
                            .add("properties", json::Value().setObject(
                                json::Object()
                                .add("type", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("string"))
                                ))
                                .add("level", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("integer"))
                                    .add("minimum", json::Value().setInteger(0))
                                    .add("maximum", json::Value().setInteger(6))
                                ))
                                .add("stream", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("string"))
                                ))
                                .add("file", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("string"))
                                ))
                                .add("size", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("integer"))
                                    .add("minimum", json::Value().setInteger(1))
                                ))
                                .add("formatter", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("string"))
                                ))
                            ))
                            .add("additionalProperties", json::Value().setBoolean(false))
                        ))
                    ))
                    .add("loggers", json::Value().setObject(
                        json::Object()
                        .add("type", json::Value().setString("object"))
                        .add("required", json::Value().setArray(
                            json::Array()
                            .add(json::Value().setString("root"))
                        ))
                        .add("properties", json::Value().setObject(
                            json::Object()
                            .add("root", json::Value().setObject(
                                json::Object()
                                .add("type", json::Value().setString("object"))
                                .add("required", json::Value().setArray(
                                    json::Array()
                                    .add(json::Value().setString("level"))
                                    .add(json::Value().setString("handlers"))
                                ))
                                .add("properties", json::Value().setObject(
                                    json::Object()
                                    .add("level", json::Value().setObject(
                                        json::Object()
                                        .add("type", json::Value().setString("integer"))
                                        .add("minimum", json::Value().setInteger(0))
                                        .add("maximum", json::Value().setInteger(6))
                                    ))
                                    .add("handlers", json::Value().setObject(
                                        json::Object()
                                        .add("type", json::Value().setString("array"))
                                        .add("minItems", json::Value().setInteger(1))
                                        .add("uniqueItems", json::Value().setBoolean(true))
                                        .add("items", json::Value().setObject(
                                            json::Object()
                                            .add("type", json::Value().setString("string"))
                                        ))
                                    ))
                                ))
                            ))
                        ))
                        .add("additionalProperties", json::Value().setObject(
                            json::Object()
                            .add("type", json::Value().setString("object"))
                            .add("properties", json::Value().setObject(
                                json::Object()
                                .add("level", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("integer"))
                                    .add("minimum", json::Value().setInteger(0))
                                    .add("maximum", json::Value().setInteger(6))
                                ))
                                .add("handlers", json::Value().setObject(
                                    json::Object()
                                    .add("type", json::Value().setString("array"))
                                    .add("minItems", json::Value().setInteger(1))
                                    .add("uniqueItems", json::Value().setBoolean(true))
                                    .add("items", json::Value().setObject(
                                        json::Object()
                                        .add("type", json::Value().setString("string"))
                                    ))
                                ))
                            ))
                            .add("additionalProperties", json::Value().setBoolean(false))
                        ))
                    ))
                ))
                .add("additionalProperties", json::Value().setBoolean(false))
            );

        public:

            JsonUtils() = delete;

            ~JsonUtils() = delete;

            static std::string getConfigurationSchema(size_t indent = 4, const std::string& newline = "\n");

            static exqudens::log::model::Configuration toConfiguration(const std::string& value, bool& valid, std::string& errorMessage);

            static exqudens::log::model::Configuration toConfiguration(const std::string& value);

        private:

            static std::string join(const std::vector<std::string>& part1 = {}, const std::vector<std::string>& part2 = {}, const std::string& delimiter = ".");

            static std::vector<std::string> add(const std::vector<std::string>& part1 = {}, const std::vector<std::string>& part2 = {});

            static json::Value parse(const std::string& value, bool& valid, std::string& errorMessage);

            static json::Value getConfigurationSchemaJsonValue();

            static exqudens::log::model::Configuration toConfiguration(const json::Value& jsonValue, bool& valid, std::string& errorMessage);

            static exqudens::log::model::FormatterConfiguration toFormatterConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys
            );

            static exqudens::log::model::FormatterConfiguration::Parameter toFormatterConfigurationParameter(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys
            );

            static exqudens::log::model::HandlerConfiguration toHandlerConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys
            );

            static exqudens::log::model::LoggerConfiguration toLoggerConfiguration(
                const json::Value& jsonValue,
                const std::vector<std::string>& parentKeys,
                const std::optional<exqudens::log::model::LoggerConfiguration>& rootLoggerConfiguration = {}
            );

            static std::string toString(const std::set<std::string>& value);

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>
#include <numeric>
#include <limits>

#include "exqudens/log/util/json/Serializer.hpp"
#include "exqudens/log/util/json/Parser.hpp"
#include "exqudens/log/util/json/Schema.hpp"
#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/util/ModelUtils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::util {

    EXQUDENS_LOG_INLINE std::string JsonUtils::getConfigurationSchema(size_t indent, const std::string& newline) {
        try {
            json::Value value = getConfigurationSchemaJsonValue();
            std::string result = json::Serializer::serialize(value, indent, newline);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration JsonUtils::toConfiguration(const std::string& value, bool& valid, std::string& errorMessage) {
        try {
            json::Value valueJson = parse(value, valid, errorMessage);
            exqudens::log::model::Configuration result = {};
            if (valid) {
                result = toConfiguration(valueJson, valid, errorMessage);
            }
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration JsonUtils::toConfiguration(const std::string& value) {
        try {
            bool valid = false;
            std::string errorMessage = {};
            exqudens::log::model::Configuration result = toConfiguration(value, valid, errorMessage);
            if (!valid) {
                throw std::runtime_error(CALL_INFO + ": " + errorMessage);
            }
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

    EXQUDENS_LOG_INLINE json::Value JsonUtils::parse(const std::string& value, bool& valid, std::string& errorMessage) {
        try {
            json::Parser parser(value);
            json::Value result = parser.parse();
            json::Value schema = getConfigurationSchemaJsonValue();
            valid = json::Schema::validate(schema, result, errorMessage);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE json::Value JsonUtils::getConfigurationSchemaJsonValue() {
        try {
            return configurationSchema;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::Configuration JsonUtils::toConfiguration(const json::Value& jsonValue, bool& valid, std::string& errorMessage) {
        try {
            json::Object jsonObject = jsonValue.getObject();

            exqudens::log::model::Configuration result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("formatters") == jsonObjectPair.first) {
                    json::Object formattersJsonObject = jsonObjectPair.second.getObject();
                    for (const auto& formattersJsonObjectPair : formattersJsonObject) {
                        auto formatter = toFormatterConfiguration(
                            formattersJsonObjectPair.second,
                            {jsonObjectPair.first, formattersJsonObjectPair.first}
                        );
                        formatter.id = formattersJsonObjectPair.first;
                        result.formatters[formatter.id] = formatter;
                    }
                } else if (std::string("handlers") == jsonObjectPair.first) {
                    json::Object handlersJsonObject = jsonObjectPair.second.getObject();
                    for (const auto& handlersJsonObjectPair : handlersJsonObject) {
                        auto handler = toHandlerConfiguration(
                            handlersJsonObjectPair.second,
                            {jsonObjectPair.first, handlersJsonObjectPair.first}
                        );
                        handler.id = handlersJsonObjectPair.first;
                        result.handlers[handler.id] = handler;
                    }
                } else if (std::string("loggers") == jsonObjectPair.first) {
                    json::Object loggersJsonObject = jsonObjectPair.second.getObject();
                    auto rootLogger = toLoggerConfiguration(
                        loggersJsonObject.at(exqudens::log::model::Constant::LOGGER_ID_ROOT),
                        {jsonObjectPair.first, exqudens::log::model::Constant::LOGGER_ID_ROOT}
                    );
                    rootLogger.id = exqudens::log::model::Constant::LOGGER_ID_ROOT;
                    result.loggers[rootLogger.id] = rootLogger;
                    for (const auto& loggersJsonObjectPair : loggersJsonObject) {
                        if (loggersJsonObjectPair.first == exqudens::log::model::Constant::LOGGER_ID_ROOT) {
                            continue;
                        }
                        auto logger = toLoggerConfiguration(
                            loggersJsonObjectPair.second,
                            {jsonObjectPair.first, loggersJsonObjectPair.first},
                            rootLogger
                        );
                        logger.id = loggersJsonObjectPair.first;
                        result.loggers[logger.id] = logger;
                    }
                } else {
                    throw std::runtime_error(CALL_INFO + ": json unexpected key: '" + jsonObjectPair.first + "'!");
                }
            }

            for (const auto& loggersPair : result.loggers) {
                for (size_t i = 0; i < loggersPair.second.handlers.size(); i++) {
                    if (!result.handlers.contains(loggersPair.second.handlers.at(i))) {
                        valid = false;
                        errorMessage = "[loggers] -> [" + loggersPair.first + "] -> [handlers] -> [" + std::to_string(i) + "] 'handlers' not contains: '" + loggersPair.second.handlers.at(i) + "'";
                        return result;
                    }
                }
            }

            for (const auto& handlersPair : result.handlers) {
                if (!result.formatters.contains(handlersPair.second.formatter)) {
                    valid = false;
                    errorMessage = "[handlers] -> [" + handlersPair.first + "] -> [formatter] 'formatters' not contains: '" + handlersPair.second.formatter + "'";
                    return result;
                }
                if (
                    handlersPair.second.type == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE
                    && !exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAMS.contains(handlersPair.second.stream)
                ) {
                    valid = false;
                    errorMessage = "[handlers] -> [" + handlersPair.first + "] -> [stream] not supported: '" + handlersPair.second.stream + "' supported: " + toString(exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAMS);
                    return result;
                }
                if (
                    handlersPair.second.type == exqudens::log::model::Constant::HANDLER_TYPE_FILE
                    && handlersPair.second.file.empty()
                ) {
                    valid = false;
                    errorMessage = "[handlers] -> [" + handlersPair.first + "] -> [file] is empty or not set";
                    return result;
                }
            }

            valid = true;
            errorMessage = "";

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE exqudens::log::model::FormatterConfiguration JsonUtils::toFormatterConfiguration(
        const json::Value& jsonValue,
        const std::vector<std::string>& parentKeys
    ) {
        try {
            json::Object jsonObject = jsonValue.getObject();
            exqudens::log::model::FormatterConfiguration result = {};
            result.parameters = exqudens::log::util::ModelUtils::defaultFormatterParameters();

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("format") == jsonObjectPair.first) {
                    result.format = jsonObjectPair.second.getString();
                } else if (std::string("parameters") == jsonObjectPair.first) {
                    json::Object parametersJsonObject = jsonObjectPair.second.getObject();
                    for (const auto& parametersJsonObjectPair : parametersJsonObject) {
                        auto parameter = toFormatterConfigurationParameter(
                            parametersJsonObjectPair.second,
                            add(parentKeys, {jsonObjectPair.first, parametersJsonObjectPair.first})
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
        const std::vector<std::string>& parentKeys
    ) {
        try {
            json::Object jsonObject = jsonValue.getObject();
            exqudens::log::model::FormatterConfiguration::Parameter result = {};

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("format") == jsonObjectPair.first) {
                    result.format = jsonObjectPair.second.getString();
                } else if (std::string("seconds") == jsonObjectPair.first) {
                    result.seconds = static_cast<uint16_t>(jsonObjectPair.second.getInteger());
                } else if (std::string("size") == jsonObjectPair.first) {
                    result.seconds = static_cast<size_t>(jsonObjectPair.second.getInteger());
                } else if (std::string("reverse") == jsonObjectPair.first) {
                    result.name = jsonObjectPair.second.getBoolean();
                } else if (std::string("name") == jsonObjectPair.first) {
                    result.name = jsonObjectPair.second.getBoolean();
                } else if (std::string("base") == jsonObjectPair.first) {
                    result.base = jsonObjectPair.second.getString();
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
            json::Object jsonObject = jsonValue.getObject();

            exqudens::log::model::HandlerConfiguration result = {};
            result.level = exqudens::log::model::Constant::LOGGER_LEVEL_ID_TRACE;
            result.stream = exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAM_OUT;
            result.size = std::numeric_limits<std::intmax_t>::max();

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("type") == jsonObjectPair.first) {
                    result.type = jsonObjectPair.second.getString();
                } else if (std::string("level") == jsonObjectPair.first) {
                    result.level = static_cast<uint16_t>(jsonObjectPair.second.getInteger());
                } else if (std::string("stream") == jsonObjectPair.first) {
                    result.stream = jsonObjectPair.second.getString();
                } else if (std::string("file") == jsonObjectPair.first) {
                    result.file = jsonObjectPair.second.getString();
                } else if (std::string("size") == jsonObjectPair.first) {
                    result.size = static_cast<size_t>(jsonObjectPair.second.getInteger());
                } else if (std::string("formatter") == jsonObjectPair.first) {
                    result.formatter = jsonObjectPair.second.getString();
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
        const std::vector<std::string>& parentKeys,
        const std::optional<exqudens::log::model::LoggerConfiguration>& rootLoggerConfiguration
    ) {
        try {
            if (parentKeys.empty()) {
                throw std::runtime_error(CALL_INFO + ": 'parentKeys' is empty!");
            }

            json::Object jsonObject = jsonValue.getObject();

            exqudens::log::model::LoggerConfiguration result = rootLoggerConfiguration.value_or({});

            for (const auto& jsonObjectPair : jsonObject) {
                if (std::string("level") == jsonObjectPair.first) {
                    result.level = static_cast<uint16_t>(jsonObjectPair.second.getInteger());
                } else if (std::string("handlers") == jsonObjectPair.first) {
                    std::vector<std::string> handlers = {};
                    json::Array jsonArray = jsonObjectPair.second.getArray();
                    for (size_t i = 0; i < jsonArray.size(); i++) {
                        std::string handler = jsonArray.at(i).getString();
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

    EXQUDENS_LOG_INLINE std::string JsonUtils::toString(const std::set<std::string>& value) {
        std::string result = "";
        std::string delimiter = "', '";
        for (const std::string& v : value) {
            if (!result.empty()) {
                result += delimiter;
            }
            result += v;
        }
        return "[" + result + "]";
    }

}

#undef CALL_INFO
