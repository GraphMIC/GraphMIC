#include <stdlib.h>
#include <iostream>

#include "gmApp.hpp"
#include <meta_graphmic.hpp>

#include "gmModulePreview.hpp"
#include "gmModuleViewer.hpp"
#include "gmModuleCore.hpp"
#include "gmModuleLogic.hpp"
#include "gmModulePython.hpp"

auto main(int argc, char *argv[]) -> int
{
    
#ifdef  __APPLE__
    setenv("QML_BAD_GUI_RENDER_LOOP", "1", 1);
#endif
    
    auto app = new gm::Application();
    
    app->setAppName(gm::Meta::appName);
    app->setOrgName(gm::Meta::orgName);
    app->setOrgDomain(gm::Meta::orgDomain);
    app->setVersionString(gm::Meta::versionString);
    app->setResourceFile("/qml/app.qml");
    
    app->use<gm::Module::Logic>();
    app->use<gm::Module::Core>();
    app->use<gm::Module::Viewer>();
    app->use<gm::Module::Preview>();
    app->use<gm::Module::Python>();
    
    app->exec(argc, argv);
    
}
