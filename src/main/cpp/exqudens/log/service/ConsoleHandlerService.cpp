#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/service/ConsoleHandlerService.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    void ConsoleHandlerService::write(const std::string& value) {
        try {
            std::cout << value << std::endl;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
