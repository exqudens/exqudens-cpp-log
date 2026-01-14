/*!
* @author Andrii Gorin
* @copyright MIT License.
*/

#pragma once

#include <optional>
#include <chrono>
#include <thread>

#include "exqudens/log/export.hpp"

namespace exqudens::log::model {

    struct EXQUDENS_LOG_API_EXPORT Data {

        std::optional<std::chrono::system_clock::time_point> timePoint = {};
        std::optional<std::thread::id> threadId = {};

    };

}
