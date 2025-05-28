#pragma once

#include <cstddef>
#include <string>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Handler.hpp"
#include "exqudens/log/model/Data.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT IHandlerService {

        public:

            virtual void configure(const exqudens::log::model::Handler& config) = 0;

            virtual bool isConfigured() = 0;

            virtual std::string toString(
                exqudens::log::model::Data& data,
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) = 0;

            virtual void writeString(const std::string& value) = 0;

            virtual void write(
                exqudens::log::model::Data& data,
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) = 0;

            virtual ~IHandlerService() = default;

    };

}
