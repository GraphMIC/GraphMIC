#include "gmModuleDialog.hpp"

#include "gmDialogController.hpp"
#include "gmDialogDeleteFile.hpp"

namespace gm
{
    namespace Module
    {
        auto Dialog::Initialize() -> void
        {
            auto controller = gm::Dialog::Controller::Create();
            registerController(controller, "Dialog");
            
            registerType<gm::Dialog::DeleteFile>();
        }
    }
}
