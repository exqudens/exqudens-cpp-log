#include <stdexcept>
#include <filesystem>

#include "exqudens/log/service/HandlerService.hpp"
#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/util/Utils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    HandlerService::HandlerService() = default;

    void HandlerService::configure(const exqudens::log::model::Handler& config) {
        try {
            formatter = std::make_shared<FormatterService>();
            formatter->configure(config.formatter);
            if (!formatter->isConfigured()) {
                throw std::runtime_error(CALL_INFO + ": formatter: '" + config.formatter.id + "' is not configured");
            }
            if (config.type == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE) {
                if (!exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAMS.contains(config.stream)) {
                    std::string errorMessage = CALL_INFO + ": handler: '" + config.id + "' wrong 'stream': '" + config.stream + "' supported: ";
                    errorMessage += exqudens::log::util::Utils::joinSet("['", exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAMS, "', '", "']");
                    throw std::runtime_error(errorMessage);
                }
            } else if (config.type == exqudens::log::model::Constant::HANDLER_TYPE_FILE) {
                if (config.file.empty()) {
                    throw std::runtime_error(CALL_INFO + ": handler: '" + config.id + "' empty 'file'");
                }
                try {
                    std::filesystem::path filePath(config.file);
                    if (!filePath.parent_path().empty()) {
                        std::filesystem::create_directories(filePath.parent_path());
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error(CALL_INFO + ": handler: '" + config.id + "' error with 'file': " + e.what());
                }
            }
            stream = config.stream;
            file = config.file;
            size = config.size;
            configured = true;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    bool HandlerService::isConfigured() {
        return configured;
    }

    std::string HandlerService::toString(
        exqudens::log::model::Data& data,
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) {
        try {
            std::string result = formatter->toString(
                data,
                file,
                line,
                function,
                id,
                level,
                message
            );
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    void HandlerService::writeString(const std::string& value) {
        try {
            throw std::runtime_error(CALL_INFO + ": unimplemented");
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    void HandlerService::write(
        exqudens::log::model::Data& data,
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) {
        try {
            std::string event = toString(
                data,
                file,
                line,
                function,
                id,
                level,
                message
            );
            writeString(event);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    HandlerService::~HandlerService() = default;

}

#undef CALL_INFO
