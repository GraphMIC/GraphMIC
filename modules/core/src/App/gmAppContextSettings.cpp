#include "gmAppContextSettings.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Settings* Settings::instance = nullptr;
            
            Settings::Settings() : Base("Settings")
            {
                log_trace(Log::New);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }
            
            auto Settings::Create() -> Settings*
            {
                log_trace(Log::Func);
                
                return new Settings();
            }
            
            Settings::~Settings()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}