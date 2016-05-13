#include "gmDialogSettings.hpp"

namespace gm
{
    namespace Dialog
    {
        Settings* Settings::instance = nullptr;
        
        Settings::Settings() : Base("Settings")
        {
            log_trace(Log::New, this);
        }
        
        auto Settings::Show() -> void
        {
            log_trace(Log::Func);
            
            if (!instance)
            {
                instance = new Settings();
            }
            
            instance->show();
        }
    }
}
