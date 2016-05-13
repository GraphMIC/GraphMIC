#include "gmModuleTest.hpp"

#include "gmTestController.hpp"
#include "gmTestUnit.hpp"
#include "gmTestCase.hpp"

namespace gm
{
    namespace Module
    {
        auto Test::Initialize() -> void
        {
            log_trace(Log::Func);
            
            registerController(gm::Test::Controller::Create(), "test");

            registerType<gm::Test::Unit>();
            registerType<gm::Test::Case>();
        }
    }
}