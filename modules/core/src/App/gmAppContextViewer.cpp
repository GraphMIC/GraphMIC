#include "gmAppContextViewer.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Viewer* Viewer::instance = nullptr;
            
            Viewer::Viewer() : Base("Viewer")
            {
                log_trace(Log::New);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }
            
            auto Viewer::Create() -> Viewer*
            {
                log_trace(Log::Func);
                
                return new Viewer();
            }
            
            Viewer::~Viewer()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}