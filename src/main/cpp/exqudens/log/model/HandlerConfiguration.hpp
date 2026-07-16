/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <cstddef>
#include <string>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT HandlerConfiguration {

        std::string id = {};
        std::string type = {};
        uint16_t level = 0;
        std::string stream = {};
        std::string file = {};
        size_t size = 0;
        std::string formatter = {};

    };

}
