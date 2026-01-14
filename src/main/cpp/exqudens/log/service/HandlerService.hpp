/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <string>
#include <memory>

#include "exqudens/log/service/IHandlerService.hpp"
#include "exqudens/log/service/FormatterService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT HandlerService : public IHandlerService {

        protected:

            std::shared_ptr<FormatterService> formatter = nullptr;
            std::string stream = {};
            std::string file = {};
            size_t size = 0;
            bool configured = false;

        public:

            HandlerService();

            void configure(const exqudens::log::model::Handler& config) override;

            bool isConfigured() override;

            std::string toString(
                exqudens::log::model::Data& data,
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) override;

            void writeString(const std::string& value) override;

            void write(
                exqudens::log::model::Data& data,
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) override;

            ~HandlerService() override;

    };

}

// implementation ---

#include <stdexcept>
#include <filesystem>

#include "exqudens/log/model/Constant.hpp"
#include "exqudens/log/util/Utils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    EXQUDENS_LOG_INLINE HandlerService::HandlerService() = default;

    EXQUDENS_LOG_INLINE void HandlerService::configure(const exqudens::log::model::Handler& config) {
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

    EXQUDENS_LOG_INLINE bool HandlerService::isConfigured() {
        return configured;
    }

    EXQUDENS_LOG_INLINE std::string HandlerService::toString(
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

    EXQUDENS_LOG_INLINE void HandlerService::writeString(const std::string& value) {
        try {
            throw std::runtime_error(CALL_INFO + ": unimplemented");
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    EXQUDENS_LOG_INLINE void HandlerService::write(
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

    EXQUDENS_LOG_INLINE HandlerService::~HandlerService() = default;

}

#undef CALL_INFO
