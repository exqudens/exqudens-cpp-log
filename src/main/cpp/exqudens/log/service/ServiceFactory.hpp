#pragma once

#include <functional>
#include <memory>

#include "exqudens/log/export.hpp"
#include "exqudens/log/model/Handler.hpp"
#include "exqudens/log/service/IHandlerService.hpp"

namespace exqudens::log::service {

    class EXQUDENS_LOG_EXPORT ServiceFactory {

        private:

            std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createConsoleHandlerFunction = {};
            std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createFileHandlerFunction = {};
            std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createHandlerFunction = {};

        public:

            static ServiceFactory& init(
                const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createConsoleHandlerFunction,
                const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createFileHandlerFunction,
                const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
            );

            static ServiceFactory& init(
                const std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)>& createHandlerFunction
            );

            static ServiceFactory& init();

            static ServiceFactory& getInstance();

            std::shared_ptr<IHandlerService> createConsoleHandler(const exqudens::log::model::Handler& config);

            std::shared_ptr<IHandlerService> createFileHandler(const exqudens::log::model::Handler& config);

            std::shared_ptr<IHandlerService> createHandler(const exqudens::log::model::Handler& config);

        private:

            static std::shared_ptr<IHandlerService> internalCreateConsoleHandler(const exqudens::log::model::Handler& config);

            static std::shared_ptr<IHandlerService> internalCreateFileHandler(const exqudens::log::model::Handler& config);

            ServiceFactory(
                std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createConsoleHandlerFunction,
                std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createFileHandlerFunction,
                std::function<std::shared_ptr<IHandlerService>(const exqudens::log::model::Handler&)> createHandlerFunction
            );

            ~ServiceFactory();

    };

}
