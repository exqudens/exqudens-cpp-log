#pragma once

#include <set>

#include "exqudens/log/export.hpp"
#include "exqudens/log/api/Logging.hpp"
#include "exqudens/log/model/Configuration.hpp"

namespace exqudens {

    class EXQUDENS_LOG_EXPORT Log {

        public:

            Log() = delete;

            ~Log() = delete;

            static log::model::Configuration defaultConfiguration(const std::set<std::string>& loggerIds = {});

    };

}
