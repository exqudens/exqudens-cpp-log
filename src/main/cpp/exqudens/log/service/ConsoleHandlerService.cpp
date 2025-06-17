#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/service/ConsoleHandlerService.hpp"
#include "exqudens/log/model/Constant.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    void ConsoleHandlerService::writeString(const std::string& value) {
        try {
            if (stream == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAM_OUT) {
                std::cout << value << std::endl;
            } else if (stream == exqudens::log::model::Constant::HANDLER_TYPE_CONSOLE_STREAM_ERR) {
                std::cerr << value << std::endl;
            } else {
                throw std::runtime_error(CALL_INFO + ": unsupported 'stream': '" + stream + "'");
            }
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
