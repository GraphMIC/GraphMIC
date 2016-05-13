#include "gmPythonNodeComponent.hpp"
#include "gmPythonNodeObject.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Component::Component(gm::Component::Type componentType, Object* node) : m_componentType(componentType), m_node(node)
            {
                this->m_selected = false;
            }

            auto Component::setSelected(bool selected) -> void
            {
                if (this->m_selected != selected)
                {
                    this->m_selected = selected;
                    emit this->selectedChanged();
                }
            }

            auto Component::isSelected() -> bool
            {
                return this->m_selected;
            }

            auto Component::select() -> void
            {
                this->m_node->setSelected(this);
                this->setSelected(true);
            }

            auto Component::remove() -> void
            {
                if (this->m_componentType == gm::Component::Type::Input)
                {
                    this->m_node->deleteInput(reinterpret_cast<Input*>(this));
                }
                else if (this->m_componentType == gm::Component::Type::Output)
                {
                    this->m_node->deleteOutput(reinterpret_cast<Output*>(this));
                }
                else
                {
                    this->m_node->deleteParam(reinterpret_cast<Param*>(this));
                }
            }

            auto Component::setName(const QString& name) -> void
            {
                this->m_name = name;
                emit this->nameChanged();
            }

            auto Component::getName() -> QString
            {
                return this->m_name;
            }

            auto Component::getComponentType() -> gm::Component::Type
            {
                return this->m_componentType;
            }
        }
    }
}