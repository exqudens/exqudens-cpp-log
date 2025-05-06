#pragma once

#include <cstddef>
#include <string>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Formatter.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT FormatterService {

        private:

            std::string format = {};
            bool configured = false;

        public:

            FormatterService();

            void configure(const exqudens::log::model::Formatter& config);

            bool isConfigured();

            std::string toString(
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
