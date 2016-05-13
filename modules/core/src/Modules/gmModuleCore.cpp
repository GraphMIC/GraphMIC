#include "gmModuleCore.hpp"

#include "gmApp.hpp"

#include "gmModuleDebug.hpp"
#include "gmModuleConnection.hpp"
#include "gmModuleData.hpp"
#include "gmModuleDialog.hpp"
#include "gmModuleNode.hpp"
#include "gmModuleNotification.hpp"
#include "gmModuleParam.hpp"
#include "gmModuleSlot.hpp"
#include "gmModuleApp.hpp"
#include "gmModuleUtil.hpp"

namespace gm
{
    namespace Module
    {
        auto Core::Initialize() -> void
        {
            log_trace(Log::Func);
            
            Application::instance->use<gm::Module::App>();
            Application::instance->use<gm::Module::Debug>();
            Application::instance->use<gm::Module::Node>();
            Application::instance->use<gm::Module::Param>();
            Application::instance->use<gm::Module::Data>();
            Application::instance->use<gm::Module::Connection>();
            Application::instance->use<gm::Module::Util>();
            Application::instance->use<gm::Module::Slot>();
            Application::instance->use<gm::Module::Notification>();
            Application::instance->use<gm::Module::Dialog>();
        }
    }
}
