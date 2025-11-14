#include <memory>
#include <utility>
#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "exqudens/log/export.hpp"
#include "exqudens/log/api/Logging.hpp"
#include "exqudens/log/model/Service.hpp"
#include "exqudens/log/service/Service.hpp"
#include "exqudens/log/util/Utils.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::api {

    Logging::Writer::Writer(
        std::string file,
        size_t line,
        std::string function,
        std::string id,
        unsigned short level
    ):
        file(std::move(file)),
        line(line),
        function(std::move(function)),
        id(std::move(id)),
        level(level) {
    }

    Logging::Writer::~Writer() {
        Logging::write(
            file,
            line,
            function,
            id,
            level,
            stream.str()
        );
    }

    std::string Logging::configure(const std::any& input) {
        try {
            if (input.type() != typeid(exqudens::log::model::Service)) {
                throw std::runtime_error(CALL_INFO + ": unsupported input type: '" + input.type().name() + "' supported type: '" + typeid(exqudens::log::model::Service).name() + "'");
            }
            exqudens::log::model::Service config = std::any_cast<exqudens::log::model::Service>(input);
            std::shared_ptr<exqudens::log::service::Service> service = std::make_shared<exqudens::log::service::Service>();
            service->configure(config);
            Logging::data = service;
            return config.id;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    bool Logging::isConfigured() {
        try {
            return Logging::data.has_value();
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    void Logging::write(
        const std::string& file,
        const size_t line,
        const std::string& function,
        const std::string& id,
        const unsigned short level,
        const std::string& message
    ) noexcept {
        try {
            if (!Logging::isConfigured()) {
                std::cerr << "not configured" << std::endl;
                return;
            }

            if (Logging::data.type() != typeid(std::shared_ptr<exqudens::log::service::Service>)) {
                std::string errorMessage = exqudens::log::util::Utils::join(
                    "wrong type",
                    {
                        ": '",
                        Logging::data.type().name(),
                        "' expected type: '",
                        typeid(std::shared_ptr<exqudens::log::service::Service>).name(),
                        "'"
                    }
                );
                std::cerr << errorMessage << std::endl;
                return;
            }

            std::shared_ptr<exqudens::log::service::Service> service = std::any_cast<std::shared_ptr<exqudens::log::service::Service>>(Logging::data);

            service->write(
                file,
                line,
                function,
                id,
                level,
                message
            );
        } catch (const std::exception& e) {
            std::cerr << exqudens::log::util::Utils::toString(e) << std::endl;
        } catch (...) {
            std::cerr << "UNHANDLED-CATCH-IN: 'exqudens::log::api::Logging::write'" << std::endl;
        }
    }

    void Logging::reset() {
        try {
            Logging::data = {};
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

}

#undef CALL_INFO
