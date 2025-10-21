#pragma once

#include "exqudens/log/service/HandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT ConsoleHandlerService : public HandlerService {

        public:

            void writeString(const std::string& value) override;

    };

}
