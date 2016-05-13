#include "gmDataNumber.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Data
    {
        Type Number::DataType = Type::Number;

        Number::Number(double value) : Base(DataType)
        {
            this->m_value = value;

            log_trace(Log::New, this);
        }

        auto Number::getIsNumber() -> bool
        {
            return true;
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

        Number::~Number()
        {
            log_trace(Log::Del, this);
        }
    }
}
