#include <stdexcept>
#include <filesystem>

#include "exqudens/log/service/FormatterService.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    FormatterService::FormatterService() = default;

    void FormatterService::configure(const exqudens::log::model::Formatter& config) {
        try {
            format = config.format;
            configured = true;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    bool FormatterService::isConfigured() {
        return configured;
    }

    std::string FormatterService::toString(
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) {
        try {
            // TODO
            std::string result = {};
            result += file;
            result += " ";
            result += std::to_string(line);
            result += " ";
            result += function;
            result += " ";
            result += id;
            result += " ";
            result += std::to_string(level);
            result += " ";
            result += message;
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    FormatterService::~FormatterService() = default;

}

#undef CALL_INFO
