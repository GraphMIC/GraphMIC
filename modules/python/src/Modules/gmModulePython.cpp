#include <boost/python.hpp>

#include "gmModulePython.hpp"

#include "gmPythonController.hpp"
#include "gmPythonEditor.hpp"
#include "gmPythonScript.hpp"
#include "gmPythonScriptList.hpp"
#include "gmPythonService.hpp"

#include "gmPythonNodeComponent.hpp"
#include "gmPythonNodeDesigner.hpp"
#include "gmPythonNodeObject.hpp"
#include "gmPythonNodeNumber.hpp"
#include "gmPythonNodeOutput.hpp"
#include "gmPythonNodeParam.hpp"
#include "gmPythonNodeInput.hpp"
#include "gmPythonNodeString.hpp"
#include "gmPythonNodeOption.hpp"
#include "gmPythonNodeBool.hpp"
#include "gmPythonNodeVector.hpp"
#include "gmPythonNodeDir.hpp"
#include "gmPythonNodeFiles.hpp"

namespace gm
{
    namespace Module
    {
        auto Python::Initialize() -> void
        {
            log_trace(Log::Func);

            auto service = gm::Python::Service::Create();
            service->prepareForThreading();

            auto controller = gm::Python::Controller::Create();
            controller->init();
            
            registerController(controller, "python");
            registerType<gm::Python::Script>();
            registerType<gm::Python::ScriptList>();
            registerType<gm::Python::Editor>();

            registerType<gm::Python::Node::Designer>();
            registerType<gm::Python::Node::Object>();
            registerType<gm::Python::Node::Component>();
            registerType<gm::Python::Node::Number>();
            registerType<gm::Python::Node::Input>();
            registerType<gm::Python::Node::Output>();
            registerType<gm::Python::Node::Option>();
            registerType<gm::Python::Node::Param>();
            registerType<gm::Python::Node::String>();
            registerType<gm::Python::Node::Bool>();
            registerType<gm::Python::Node::Vector>();
            registerType<gm::Python::Node::Dir>();
            registerType<gm::Python::Node::Files>();
        }
    }
}
