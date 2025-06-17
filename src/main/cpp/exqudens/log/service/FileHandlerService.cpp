#include <stdexcept>
#include <filesystem>

#include "exqudens/log/service/FileHandlerService.hpp"
#include "exqudens/log/util/FileHandlerUtils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    void FileHandlerService::writeString(const std::string& value) {
        try {
            if (currentFile.empty() || currentSize >= size) {
                currentFile = exqudens::log::util::FileHandlerUtils::getNextFileName(file, size);
                if (currentStream.is_open()) {
                    currentStream.close();
                }
                currentStream.open(currentFile, std::ios::app);
            }

            if (!currentStream.is_open()) {
                throw std::runtime_error(CALL_INFO + ": file 'open' failed");
            }

            currentStream << value << std::endl;

            currentSize += (value.size() + 1);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
