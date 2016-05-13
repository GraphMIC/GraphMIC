#include "gmPythonNodeOutput.hpp"
#include "gmSlotConstraints.hpp"
#include "gmDataType.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Output::Output(Object* node) : Component(gm::Component::Type::Output, node)
            {
                this->setName("output");

                this->m_dataTypeID = Data::TypeToIndex(Data::Type::Image);
                this->m_dataTypeString = Data::TypeToString(Data::TypeFromIndex(this->m_dataTypeID));
                this->m_constraints = new Slot::Constraints(std::bitset<4>("1111"), std::bitset<8>("11111111"), std::bitset<8>("11111111"), std::bitset<8>("11111111"));
            }

            auto Output::getConstraints() -> Slot::Constraints*
            {
                return this->m_constraints;
            }

            auto Output::setDataTypeID(int dataTypeID) -> void
            {
                if (this->m_dataTypeID != dataTypeID)
                {
                    this->m_dataTypeID = dataTypeID;
                    emit this->dataTypeIDChanged();

                    this->m_dataTypeString = Data::TypeToString(Data::TypeFromIndex(this->m_dataTypeID));
                    emit this->dataTypeStringChanged();
                }
            }

            auto Output::getDataTypeString() -> QString
            {
                return this->m_dataTypeString;
            }

            auto Output::getDataTypeID() -> int
            {
                return this->m_dataTypeID;
            }
        }
    }
}
