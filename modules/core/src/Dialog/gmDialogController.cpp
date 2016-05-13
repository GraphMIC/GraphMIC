#include "gmAppController.hpp"
#include "gmDialogController.hpp"
#include "gmDialogSettings.hpp"
#include "gmDialogAbout.hpp"

namespace gm
{
    namespace Dialog
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
        
        auto Controller::Create() -> Controller*
        {
            log_trace(Log::Func);
            
            return new Controller();
        }

        auto Controller::showSettings() -> void
        {
            log_trace(Log::Func);
            
            Settings::Show();
        }
        
        auto Controller::showAbout() -> void
        {
            log_trace(Log::Func);
            
            About::Show();
        }
        
        Controller::~Controller()
        {
            log_trace(Log::Del, this);
        }
    }
}
