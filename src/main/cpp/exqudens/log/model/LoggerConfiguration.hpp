/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT LoggerConfiguration {

        std::string id;
        uint16_t level;
        std::vector<std::string> handlers;

    };

}
