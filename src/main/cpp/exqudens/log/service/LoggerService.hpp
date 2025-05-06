#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <vector>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Logger.hpp"
#include "exqudens/log/service/IHandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT LoggerService {

        private:

            unsigned short level = 0;
            std::vector<std::shared_ptr<IHandlerService>> handlers = {};
            bool configured = false;

        public:

            LoggerService();

            void configure(const exqudens::log::model::Logger& config);

            bool isConfigured();

            void write(
                const std::string& file,
                const size_t line,
                const std::string& function,
                const std::string& id,
                const unsigned short level,
                const std::string& message
            );

            ~LoggerService();

    };

}
