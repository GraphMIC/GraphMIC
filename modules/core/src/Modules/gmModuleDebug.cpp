#include "gmModuleDebug.hpp"
#include "gmDebugController.hpp"

namespace gm
{
    namespace Module
    {        
        auto Debug::Initialize() -> void
        {
            registerController(gm::Debug::Controller::Create(), "debug");
        }
    }
}
