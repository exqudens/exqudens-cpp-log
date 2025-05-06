#pragma once

#include "exqudens/log/service/HandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT FileHandlerService : virtual public HandlerService {

        protected:

            void write(const std::string& value) override;

    };

}
