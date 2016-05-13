#include "gmPythonNodeString.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            String::String(Object* node) : Param(gm::Component::Type::String, node)
            {
                this->setName("string param");
            }

            auto String::setValue(const QString& value) -> void
            {
                this->m_value = value;
                emit this->valueChanged();
            }

            auto String::getValue() -> QString
            {
                return this->m_value;
            }
        }
    }
}
