#pragma once

#include <cstddef>
#include <string>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Configuration.hpp"
#include "exqudens/log/service/LoggerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT Service {

        private:

            std::map<std::string, LoggerService> loggers = {};
            bool configured = false;

        public:

            Service();

            void configure(const exqudens::log::model::Configuration& configuration);

            bool isConfigured();

            void write(
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            ) noexcept;

            ~Service();

    };

}
