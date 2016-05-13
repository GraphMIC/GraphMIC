#include "gmComponentBase.hpp"

#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"

#include "gmNodeObject.hpp"
#include "gmParamBool.hpp"
#include "gmParamNumber.hpp"
#include "gmParamString.hpp"
#include "gmParamOption.hpp"
#include "gmParamFiles.hpp"
#include "gmParamDir.hpp"
#include "gmParamVector.hpp"

#include "gmAsync.hpp"

#include "gmDebugController.hpp"

namespace gm
{
    namespace Param
    {
        class Base;
        class Int;
        class Bool;
        class Float;
        class String;
        class Option;
        class Dir;
        class Files;
        class Vector;
    }

    namespace Slot
    {
        class InputBase;
        class OutputBase;
    }
    
    namespace Component
    {
        Base::Base(Type componentType, const QString& name) : m_modified(false), m_name(name), m_node(nullptr), m_componentType(componentType)
        {
            log_trace(Log::New, this);
            
            Debug::Controller::instance->incCompCount();
        }

        auto Base::moveToMain() -> void
        {
            Async::MoveToMain(this);
        }

        auto Base::setNode(Node::Object* node) -> void
        {
            log_trace(Log::Set, node);
            
            this->m_node = node;
        }
        
        auto Base::getNode() -> Node::Object*
        {
            log_trace(Log::Get);
            
            return this->m_node;
        }
        
        auto Base::getName() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_name;
        }
        
        auto Base::getComponentType() -> Type
        {
            return this->m_componentType;
        }
        
        auto Base::setModified(bool modified) -> void
        {
            log_trace(Log::Set, modified);
            
            if (this->m_modified != modified)
            {
                this->m_modified = modified;
                emit this->modifiedChanged();
                
                if (modified && this->m_node)
                {
                    this->m_node->setModified(true);
                }
            }
        }
        
        auto Base::isModified() -> bool
        {
            return this->m_modified;
        }
        
        template <>
        auto Base::as<Slot::Base>() -> Slot::Base*
        {
            if (this->m_componentType == Component::Type::Input || this->m_componentType == Component::Type::Output)
            {
                return reinterpret_cast<Slot::Base*>(this);
            }
            
            return nullptr;
        }
        
        template <class TComponent> auto Base::as() -> TComponent*
        {
            if (this->m_componentType == TComponent::ComponentType)
            {
                return reinterpret_cast<TComponent*>(this);
            }
            
            return nullptr;
        }
        
        Base::~Base()
        {
            log_trace(Log::Del, this);
            
            Debug::Controller::instance->decCompCount();
        }
        
        template auto Base::as<Slot::InputBase>() -> Slot::InputBase*;
        template auto Base::as<Slot::OutputBase>() -> Slot::OutputBase*;
        template auto Base::as<Param::Bool>() -> Param::Bool*;
        template auto Base::as<Param::Dir>() -> Param::Dir*;
        template auto Base::as<Param::Files>() -> Param::Files*;
        template auto Base::as<Param::Number>() -> Param::Number*;
        template auto Base::as<Param::String>() -> Param::String*;
        template auto Base::as<Param::Option>() -> Param::Option*;
        template auto Base::as<Param::Vector>() -> Param::Vector*;
    }
}
