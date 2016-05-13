#include "gmNodePropertyController.hpp"

#include "gmInterfacePreviewController.hpp"
#include "gmNodeObject.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Node
    {
        PropertyController* PropertyController::instance = nullptr;
        
        PropertyController::PropertyController() : m_node(nullptr), m_expanded(false)
        {
            if (instance)
            {
                throw new std::runtime_error("instance already existing");
            }
            
            instance = this;
        }
        
        auto PropertyController::Create() -> PropertyController*
        {
            return new PropertyController();
        }
        
        auto PropertyController::setExpanded(bool expanded) -> void
        {
            log_trace(Log::Set, expanded);
            
            if (this->m_expanded != expanded)
            {
                this->m_expanded = expanded;
                emit this->expandedChanged();
            }
        }

        auto PropertyController::getExpanded() -> bool
        {
            return this->m_expanded;
        }

        auto PropertyController::reset() -> void
        {
            log_trace(Log::Func);

            if (this->m_node)
            {
                this->m_node = nullptr;
                emit this->nodeChanged();
            }
        }

        auto PropertyController::setNode(Object* node) -> void
        {
            log_trace(Log::Set, node);
            
            this->m_node = node;
            emit this->nodeChanged();
            
            Interface::Preview::Controller::instance->setNode(this->m_node);
        }
        
        auto PropertyController::getNode() -> Object*
        {
            return this->m_node;
        }
        
        PropertyController::~PropertyController()
        {
            log_trace(Log::Del, this);
        }
    }
}
