#include "gmModuleController.hpp"
#include "gmModuleBase.hpp"

#include <QQmlComponent>

namespace gm
{
    namespace Module
    {
        Controller* Controller::instance = nullptr;
        
        Controller::Controller()
        {
            log_trace(Log::New, this);
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }

        auto Controller::bla(QObject* controller, const QString& name) -> void //TODO: remove this function
        {
            App::Controller::registerController(controller, name);
        }
        
        auto Controller::Create() -> Controller*
        {
            log_trace(Log::Func);
            
            return new Controller();
        }
    }
}