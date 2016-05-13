#include "gmAppSidebar.hpp"

#include "gmAppContextController.hpp"
#include "gmApp.hpp"

#include "gmLog.hpp"

#include <iostream>

namespace gm
{
    namespace App
    {
        Sidebar* Sidebar::instance = nullptr;
        
        Sidebar::Sidebar()
        {
            log_trace(Log::New, this);
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }
        
        auto Sidebar::Create() -> Sidebar*
        {
            return new Sidebar();
        }
        
        Sidebar::~Sidebar()
        {
            log_trace(Log::Del, this);
            
            instance = nullptr;
        }
    }
}
