#pragma once

#include <fstream>

#include "exqudens/log/service/HandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_API_EXPORT FileHandlerService : public HandlerService {

        private:

            size_t currentSize = 0;
            std::string currentFile = {};
            std::ofstream currentStream = {};

        protected:

            void writeString(const std::string& value) override;

    };

}
