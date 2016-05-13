#include "gmAppContextPython.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Python* Python::instance = nullptr;
            
            Python::Python() : Base("Python")
            {
                log_trace(Log::New);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }
            
            auto Python::Create() -> Python*
            {
                log_trace(Log::Func);
                
                return new Python();
            }
            
            Python::~Python()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}