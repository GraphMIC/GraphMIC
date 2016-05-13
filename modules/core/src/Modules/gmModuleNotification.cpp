#include "gmModuleNotification.hpp"

#include "gmNotificationController.hpp"
#include "gmNotificationEntry.hpp"
#include "gmNotificationList.hpp"

namespace gm
{
    namespace Module
    {        
        auto Notification::Initialize() -> void
        {
            auto controller = gm::Notification::Controller::Create();
            registerController(controller, "notifications");
            
            registerType<gm::Notification::Controller>();
            registerType<gm::Notification::Entry>();
            registerType<gm::Notification::List>();
        }
    }
}
