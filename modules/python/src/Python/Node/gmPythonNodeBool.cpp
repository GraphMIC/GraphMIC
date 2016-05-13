#include "gmPythonNodeBool.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Bool::Bool(Object* node) : Param(gm::Component::Type::Bool, node), m_value(false)
            {
                this->setName("bool param");
            }

            auto Bool::setValue(bool value) -> void
            {
                if (this->m_value != value)
                {
                    this->m_value = value;
                    emit this->valueChanged();
                }
            }

            auto Bool::getValue() -> bool
            {
                return this->m_value;
            }
        }
    }
}
