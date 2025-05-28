#pragma once

#include <cstddef>
#include <string>
#include <memory>

#include "exqudens/log/service/IHandlerService.hpp"
#include "exqudens/log/service/FormatterService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT HandlerService : public IHandlerService {

        protected:

            std::shared_ptr<FormatterService> formatter = nullptr;
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
