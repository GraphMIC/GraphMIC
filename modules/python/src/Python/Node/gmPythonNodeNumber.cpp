#include "gmPythonNodeNumber.hpp"

#include <limits>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Number::Number(Object* node) : Param(gm::Component::Type::Number, node), m_value(0)
            {
                this->setName("number param");
                this->m_min = -std::numeric_limits<double>::max();
                this->m_max = std::numeric_limits<double>::max();
            }

            auto Number::setValue(double value) -> void
            {
                this->m_value = value;
                emit this->valueChanged();
            }

            auto Number::getValue() -> double
            {
                return this->m_value;
            }

            auto Number::setMin(double min) -> void
            {
                this->m_min = min;
                emit this->minChanged();
            }

            auto Number::getMin() -> double
            {
                return this->m_min;
            }

            auto Number::setMax(double max) -> void
            {
                this->m_max = max;
                emit this->maxChanged();
            }

            auto Number::getMax() -> double
            {
                return this->m_max;
            }
        }
    }
}
