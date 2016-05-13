#include "gmDialogAbout.hpp"

namespace gm
{
    namespace Dialog
    {
        About* About::instance = nullptr;
        
        About::About() : Base("About")
        {
            log_trace(Log::New, this);
        }
        
        auto About::Show() -> void
        {
            log_trace(Log::Func);
            
            if (!instance)
            {
                instance = new About();
            }
            
            instance->show();
        }
    }
}
