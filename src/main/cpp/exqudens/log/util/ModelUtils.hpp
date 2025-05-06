#pragma once

#include <string>
#include <map>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Configuration.hpp"
#include "exqudens/log/model/Logger.hpp"

namespace exqudens::log::util {

    class EXQUDENS_LOG_EXPORT ModelUtils {

        public:

            ModelUtils() = delete;

            ~ModelUtils() = delete;

            static std::map<std::string, exqudens::log::model::Logger> toLoggerMap(const exqudens::log::model::Configuration& configuration);

    };

}
