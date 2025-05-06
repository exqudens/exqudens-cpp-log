#include <utility>
#include <stdexcept>
#include <filesystem>

#include "exqudens/log/service/ServiceFactory.hpp"
#include "exqudens/log/service/Service.hpp"
#include "exqudens/log/service/IHandlerService.hpp"
#include "exqudens/log/service/ConsoleHandlerService.hpp"
#include "exqudens/log/service/FileHandlerService.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"

namespace exqudens::log::service {

    ServiceFactory& ServiceFactory::init(
        const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
        const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
        const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
    ) {
        static ServiceFactory instance(
            createConsoleHandlerFunction,
            createFileHandlerFunction,
            createHandlerFunction
        );
        return instance;
    }

    ServiceFactory& ServiceFactory::init(
        const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
    ) {
        return init(
            &ServiceFactory::internalCreateConsoleHandler,
            &ServiceFactory::internalCreateFileHandler,
            createHandlerFunction
        );
    }

    ServiceFactory& ServiceFactory::init() {
        return init(
            &ServiceFactory::internalCreateConsoleHandler,
            &ServiceFactory::internalCreateFileHandler,
            {}
        );
    }

    ServiceFactory& ServiceFactory::getInstance() {
        return init();
    }

    std::shared_ptr<IHandlerService> ServiceFactory::createConsoleHandler(const exqudens::log::model::Handler& config) {
        try {
            return createConsoleHandlerFunction(config);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::shared_ptr<IHandlerService> ServiceFactory::createFileHandler(const exqudens::log::model::Handler& config) {
        try {
            return createFileHandlerFunction(config);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::shared_ptr<IHandlerService> ServiceFactory::createHandler(const exqudens::log::model::Handler& config) {
        try {
            return createHandlerFunction(config);
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::shared_ptr<IHandlerService> ServiceFactory::internalCreateConsoleHandler(const exqudens::log::model::Handler& config) {
        try {
            std::shared_ptr<IHandlerService> result = nullptr;
            result = std::make_unique<ConsoleHandlerService>();
            result->configure(config);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    std::shared_ptr<IHandlerService> ServiceFactory::internalCreateFileHandler(const exqudens::log::model::Handler& config) {
        try {
            std::shared_ptr<IHandlerService> result = nullptr;
            result = std::make_unique<FileHandlerService>();
            result->configure(config);
            return result;
        } catch (...) {
            std::throw_with_nested(std::runtime_error(CALL_INFO));
        }
    }

    ServiceFactory::ServiceFactory(
        std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createConsoleHandlerFunction,
        std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createFileHandlerFunction,
        std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createHandlerFunction
    ):
        createConsoleHandlerFunction(std::move(createConsoleHandlerFunction)),
        createFileHandlerFunction(std::move(createFileHandlerFunction)),
        createHandlerFunction(std::move(createHandlerFunction))
    {
    }

    ServiceFactory::~ServiceFactory() = default;

}

#undef CALL_INFO
