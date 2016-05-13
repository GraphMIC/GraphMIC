#pragma once

#include "gmLog.hpp"
#include "gmModuleController.hpp"

#include <QVariant>

namespace gm
{
    namespace Module
    {
        class Base
        {
        private:
            std::string m_identifier;
            Base() = delete;
        public:
            Base(const std::string& identifier) : m_identifier(identifier) {}
            
            ~Base() = default;
            
            template <class T>
            static auto registerController(T* controller, const QString& name) -> void
            {
                log_trace(Log::Func);
                
                Module::Controller::instance->registerController<T>(controller, name);
            }
            
            template <class T>
            static auto registerType() -> void
            {
                Module::Controller::instance->registerType<T>();
            }
            
            template <class T>
            static auto registerType(const QString& ns, const QString& name) -> void
            {
                Module::Controller::instance->registerType<T>(ns.toStdString().c_str(), name.toStdString().c_str());
            }
            
            template <class T>
            static auto registerInterface(const QString& name) -> void
            {
                Module::Controller::instance->registerInterface<T>(name);
            }
            
            auto getIdentifier() -> std::string { return this->m_identifier; }
        };
    }
}