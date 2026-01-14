/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Formatter.hpp"
#include "exqudens/log/model/Data.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT FormatterService {

        private:

            std::vector<std::string> formatParts = {};
            std::map<std::string, exqudens::log::model::Formatter::Parameter> parameters = {};
            bool configured = false;

        public:

            FormatterService();

            void configure(const exqudens::log::model::Formatter& config);

            bool isConfigured();

            std::string toString(
                exqudens::log::model::Data& data,
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            );

            ~FormatterService();

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>

#include "exqudens/log/util/FormatterUtils.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    EXQUDENS_LOG_INLINE FormatterService::FormatterService() = default;

    EXQUDENS_LOG_INLINE void FormatterService::configure(const exqudens::log::model::Formatter& config) {
        try {
            formatParts = exqudens::log::util::FormatterUtils::splitFormat(config.format, exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS, '\\');
            parameters = config.parameters;
            configured = true;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE bool FormatterService::isConfigured() {
        return configured;
    }

    EXQUDENS_LOG_INLINE std::string FormatterService::toString(
        exqudens::log::model::Data& data,
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) {
        try {
            std::string result = {};

            for (size_t i = 0; i < formatParts.size(); i++) {
                std::string formatPart = formatParts.at(i);

                if (exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDERS.contains(formatPart)) {
                    std::string value = {};
                    if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_TIMESTAMP) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_TIMESTAMP);
                        if (!data.timePoint.has_value()) {
                            data.timePoint.emplace(std::chrono::system_clock::now());
                        }
                        value = exqudens::log::util::FormatterUtils::toStringTimestamp(
                            data.timePoint.value(),
                            parameter.format,
                            parameter.seconds,
                            exqudens::log::model::Constant::FORMATTER_PARAMETER_TIMESTAMP_SECONDS_DEVIDER_MAP,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LEVEL) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LEVEL);
                        value = exqudens::log::util::FormatterUtils::toStringLevel(
                            level,
                            parameter.name,
                            exqudens::log::model::Constant::LOGGER_LEVEL_ID_NAME_MAP,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_THREAD) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_THREAD);
                        if (!data.threadId.has_value()) {
                            data.threadId.emplace(std::this_thread::get_id());
                        }
                        value = exqudens::log::util::FormatterUtils::toStringThread(
                            data.threadId.value(),
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LOGGER) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LOGGER);
                        value = exqudens::log::util::FormatterUtils::toStringLogger(
                            id,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_FUNCTION) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FUNCTION);
                        value = exqudens::log::util::FormatterUtils::toStringFunction(
                            function,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_FILE) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_FILE);
                        value = exqudens::log::util::FormatterUtils::toStringFile(
                            file,
                            parameter.base,
                            parameter.name,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_LINE) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_LINE);
                        value = exqudens::log::util::FormatterUtils::toStringLine(
                            line,
                            parameter.size,
                            parameter.reverse
                        );
                    } else if (formatPart == exqudens::log::model::Constant::FORMATTER_FORMAT_PLACE_HOLDER_MESSAGE) {
                        exqudens::log::model::Formatter::Parameter parameter = parameters.at(exqudens::log::model::Constant::FORMATTER_PARAMETER_ID_MESSAGE);
                        value = exqudens::log::util::FormatterUtils::toStringMessage(
                            message,
                            parameter.size,
                            parameter.reverse
                        );
                    } else {
                        throw std::runtime_error(CALL_INFO + ": unimplemented 'formatPart': '" + formatPart + "'");
                    }
                    result += value;
                } else {
                    result += formatPart;
                }
            }

            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE FormatterService::~FormatterService() = default;

}

#undef CALL_INFO
