#include "gmAppController.hpp"

#include "gmAppContextController.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        Controller* Controller::instance = nullptr;
        QVariantMap Controller::m_controllers;
        
        Controller::Controller()
        {
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }
            
        auto Controller::getControllers() -> QVariantMap
        {
            return m_controllers;
        }
        
        auto Controller::InstanceProvider(QQmlEngine* qmlEngine, QJSEngine* qjsEngine) -> QObject*
        {
            return instance;
        }
        
        auto Controller::registerController(QObject* controller, const QString& name) -> void
        {
            QVariant variant;
            variant.setValue(controller);
            
            m_controllers[name] = variant;
        }
        
        auto Controller::init() -> void
        {
        }
        
        auto Controller::Create() -> Controller*
        {
            return new Controller();
        }
        
        auto Controller::isDebugBuild() -> bool
        {
#ifdef NDEBUG
            return false;
#else
            return true;
#endif
        }
        
        auto Controller::setVersion(QString version) -> void
        {
            this->m_version = version;
        }
        
        auto Controller::getVersion() -> QString
        {
            return this->m_version;
        }
        
        Controller::~Controller()
        {
            instance = nullptr;
        }
    }
}