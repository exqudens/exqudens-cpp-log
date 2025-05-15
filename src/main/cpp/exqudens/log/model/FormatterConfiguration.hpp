#pragma once

#include <cstddef>
#include <string>
#include <map>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_EXPORT FormatterConfiguration {

        struct EXQUDENS_LOG_EXPORT Parameter {

            std::string id = {};
            std::string format = {};
            unsigned short seconds = 0;
            std::string base = {};
            bool name = false;
            size_t size = 0;
            bool reverse = false;

        };

        std::string id = {};
        std::string format = {};
        std::map<std::string, Parameter> parameters = {};

    };

}
