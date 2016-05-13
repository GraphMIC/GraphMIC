#include "gmModuleApp.hpp"

#include "gmAppSidebar.hpp"
#include "gmAppContextController.hpp"
#include "gmAppContextBase.hpp"
#include "gmAppContextGraph.hpp"
#include "gmAppContextPython.hpp"
#include "gmAppContextSettings.hpp"
#include "gmAppContextViewer.hpp"

namespace gm
{
    namespace Module
    {
        auto App::Initialize() -> void
        {
            auto contextController = gm::App::Context::Controller::Create();
            contextController->init();
            
            auto sidebar = gm::App::Sidebar::Create();
            
            registerController(contextController, "context");
            registerController(sidebar, "sidebar");
            
            registerType<gm::App::Context::Base>();
            registerType<gm::App::Context::Python>();
            registerType<gm::App::Context::Graph>();
            registerType<gm::App::Context::Settings>();
            registerType<gm::App::Context::Viewer>();
        }
    }
}
