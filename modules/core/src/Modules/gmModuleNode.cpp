#include "gmModuleNode.hpp"

#include "gmNodeList.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeSearch.hpp"
#include "gmNodeObject.hpp"
#include "gmNodeConnector.hpp"
#include "gmNodeSelectable.hpp"
#include "gmNodeSearchItem.hpp"
#include "gmNodePropertyController.hpp"
#include "gmNodeGraphList.hpp"

namespace gm
{
    namespace Module
    {        
        auto Node::Initialize() -> void
        {
            log_trace(Log::Func);
            
            auto nodeEditor = gm::Node::Editor::Create();
            nodeEditor->init();
            
            registerController(nodeEditor, "nodeEditor");
            registerController(gm::Node::Search::Create(), "nodeSearch");
            registerController(gm::Node::PropertyController::Create(), "nodeProperties");

            registerType<gm::Node::PropertyController>();
            registerType<gm::Node::SearchItem>();
            registerType<gm::Node::Selectable>();
            registerType<gm::Node::GraphList>();
            registerType<gm::Node::Connector>();
            registerType<gm::Node::Object>();
            registerType<gm::Node::Graph>();
            registerType<gm::Node::List>();
        }
    }
}