#include <stdexcept>
#include <filesystem>

#include "exqudens/log/service/FileHandlerService.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    void FileHandlerService::writeString(const std::string& value) {
        try {
            throw std::runtime_error(CALL_INFO + ": TODO");
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
