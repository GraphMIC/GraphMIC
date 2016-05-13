#include "gmSlotBase.hpp"
#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeConnector.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmSlotConstraints.hpp"

#include "gmAsync.hpp"

namespace gm
{
    namespace Slot
    {
        Base::Base(Component::Type componentType, Data::Type dataType, const QString& name, Constraints* constraints) : Component::Base(componentType, name), /*m_constraints(constraints),*/ m_dataType(dataType)
        {
            if (componentType == Component::Type::Input)
            {
                this->m_slotType = Type::Input;
            }
            else
            {
                this->m_slotType = Type::Output;
            }

            switch (dataType)
            {
                case Data::Type::Image: this->m_dataTypeString = "image"; break;
                case Data::Type::Number: this->m_dataTypeString = "number"; break;
                case Data::Type::Vector: this->m_dataTypeString = "vector"; break;
                case Data::Type::Pointset: this->m_dataTypeString = "pointset"; break;
            }

            this->setConstraints(constraints);
        }

        auto Base::setConstraints(Constraints* constraints) -> void
        {
            this->m_constraints = constraints;
            emit this->constraintsChanged();
        }

        auto Base::getConstraints() -> Constraints*
        {
            return this->m_constraints;
        }

        auto Base::getDataTypeString() -> QString
        {
            return this->m_dataTypeString;
        }

        auto Base::moveConnectX(int x) -> void
        {
            if (this->m_slotType == Type::Output)
            {
                Node::Connector::instance->setX2(this->m_x + x);
            }
            else
            {
                Node::Connector::instance->setX1(this->m_x + x);
            }
        }
        
        auto Base::moveConnectY(int y) -> void
        {
            if (this->m_slotType == Type::Output)
            {
                Node::Connector::instance->setY2(this->m_y + y);
            }
            else
            {
                Node::Connector::instance->setY1(this->m_y + y);
            }
        }
        
        auto Base::setConnecting(bool connecting) -> void
        {
            if (this->m_connecting != connecting)
            {
                this->m_connecting = connecting;
                
                if (connecting)
                {
                    Node::Connector::instance->setX1(this->m_x);
                    Node::Connector::instance->setY1(this->m_y);
                    Node::Connector::instance->setX2(this->m_x);
                    Node::Connector::instance->setY2(this->m_y);
                                        
                    Node::Connector::instance->setActive(true);
                }
                else
                {
                    Node::Connector::instance->setActive(false);
                }
            }
        }
        
        auto Base::getConnecting() -> bool
        {
            return this->m_connecting;
        }

        auto Base::setX(int x) -> void
        {
            this->m_x = x;
            emit this->xChanged();
            
            this->onPositionChanged();
        }
                    
        auto Base::getX() -> int
        {
            return this->m_x;
        }
                    
        auto Base::setY(int y) -> void
        {
            this->m_y = y;
            emit this->yChanged();
            
            this->onPositionChanged();
        }
                    
        auto Base::getY() -> int
        {
            return this->m_y;
        }
            
        auto Base::getDataType() -> Data::Type
        {
            return this->m_dataType;
        }

        auto Base::getSlotType() -> Slot::Type
        {
            return this->m_slotType;
        }
        
        auto Base::getSlotTypeID() -> int
        {
            return this->m_slotType == Type::Output;
        }
        
        auto Base::connect(Base* other) -> void
        {
            if (!other)
            {
                return;
            }
            
            Slot::InputBase* input = reinterpret_cast<Slot::InputBase*>(this->m_slotType == Type::Input ? this : other->m_slotType == Type::Input ? other : nullptr);
            Slot::OutputBase* output = reinterpret_cast<Slot::OutputBase*>(this->m_slotType == Type::Output ? this : other->m_slotType == Type::Output ? other : nullptr);
            
            if (input && output)
            {
                if (input->isConnected(output))
                {
                    return;
                }
                
                output->connect(input);
            }
        }

        auto Base::moveToMain() -> void
        {
            if (this->m_constraints)
            {
                Async::MoveToMain(this->m_constraints);
            }
        }

        Base::~Base()
        {
            delete this->m_constraints;
        }
    }
}