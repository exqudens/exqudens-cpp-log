#pragma once

#include "exqudens/log/service/HandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT FileHandlerService : public HandlerService {

        protected:

            void writeString(const std::string& value) override;

    };

}
