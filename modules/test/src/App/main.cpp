#include <stdlib.h>
#include <iostream>

#include "gmApp.hpp"
#include <meta_graphmic.hpp>
#include "gmModuleViewer.hpp"
#include "gmModulePreview.hpp"
#include "gmModuleLogic.hpp"
#include "gmModuleCore.hpp"
#include "gmModuleTest.hpp"
#include "gmModulePython.hpp"

auto main(int argc, char *argv[]) -> int
{
    auto app = new gm::Application();

    app->setAppName(gm::Meta::appName);
    app->setOrgName(gm::Meta::orgName);
    app->setOrgDomain(gm::Meta::orgDomain);
    app->setVersionString(gm::Meta::versionString);
    app->setResourceFile("/qml/test.qml");

    app->use<gm::Module::Test>();
    app->use<gm::Module::Logic>();
    app->use<gm::Module::Core>();
    app->use<gm::Module::Viewer>();
    app->use<gm::Module::Preview>();
    app->use<gm::Module::Python>();


    app->exec(argc, argv);

}
