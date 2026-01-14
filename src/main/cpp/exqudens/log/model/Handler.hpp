/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <string>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Formatter.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT Handler {

        std::string id;
        std::string type;
        std::string stream = {};
        std::string file = {};
        size_t size = 0;
        Formatter formatter;

    };

}
