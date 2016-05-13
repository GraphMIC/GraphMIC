#include "gmPythonNodeInput.hpp"
#include "gmSlotConstraints.hpp"
#include "gmDataType.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Input::Input(Object* node) : Component(gm::Component::Type::Input, node)
            {
                this->setName("input");

                this->m_dataTypeID = Data::TypeToIndex(Data::Type::Image);
                this->m_dataTypeString = Data::TypeToString(Data::Type::Image);
                this->m_required = true;
                this->m_constraints = new Slot::Constraints(std::bitset<4>("1111"), std::bitset<8>("11111111"), std::bitset<8>("11111111"), std::bitset<8>("11111111"));
            }

            auto Input::getConstraints() -> Slot::Constraints*
            {
                return this->m_constraints;
            }

            auto Input::setRequired(bool required) -> void
            {
                if (this->m_required != required)
                {
                    this->m_required = required;
                    emit this->requiredChanged();
                }
            }

            auto Input::isRequired() -> bool
            {
                return this->m_required;
            }

            auto Input::setDataTypeID(int dataTypeID) -> void
            {
                if (this->m_dataTypeID != dataTypeID)
                {
                    this->m_dataTypeID = std::min(std::max(0, dataTypeID), 3);
                    emit this->dataTypeIDChanged();

                    this->m_dataTypeString = Data::TypeToString(Data::TypeFromIndex(this->m_dataTypeID));
                    emit this->dataTypeStringChanged();
                }
            }
            
            auto Input::getDataTypeID() -> int
            {
                return this->m_dataTypeID;
            }

            auto Input::getDataTypeString() -> QString
            {
                return this->m_dataTypeString;
            }
        }
    }
}
