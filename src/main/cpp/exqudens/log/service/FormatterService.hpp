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
