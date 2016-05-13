#include "gmLog.hpp"

#include "gmInterfaceViewerController.hpp"

namespace gm
{
    namespace Interface
    {
        namespace Viewer
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
            
            Controller::~Controller()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}
