#include "gmParamNumber.hpp"
#include "gmSlotOutput.hpp"
#include "gmDataNumber.hpp"

#include <limits>
#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type Number::ComponentType = Component::Type::Number;

        Number::Number(const QString& name, double value, double min, double max) : Base(ComponentType, name)
        {
            log_trace(Log::New, this);

            this->m_output  = nullptr;
            this->m_value   = value;
            this->m_min     = min;
            this->m_max     = max;
        }

        Number::Number(const QString& name, double value) : Number(name, value, -std::numeric_limits<double>::max(), std::numeric_limits<double>::max()) {}

        Number::Number(const QString& name) : Number(name, 0) {}

        auto Number::link(Slot::Output<Data::Number>* output) -> void
        {
            this->m_output = output;
        }

        auto Number::setValue(double value) -> void
        {
            log_trace(Log::Set, value);

            auto lastVal = this->m_value;

            if (value > this->m_max)
            {
                this->m_value = this->m_max;
            }
            else if (value < this->m_min)
            {
                this->m_value = this->m_min;
            }
            else
            {
                this->m_value = value;
            }

            if (lastVal != this->m_value)
            {
                emit this->valueChanged();
                this->setModified(true);

                if (this->m_output)
                {
                    this->m_output->getNumber()->setValue(this->m_value);
                }
            }
        }

        auto Number::getValue() -> double
        {
            log_trace(Log::Get);

            return this->m_value;
        }

        auto Number::getIntValue() -> int
        {
            return static_cast<int>(this->m_value);
        }

        auto Number::getFloatValue() -> float
        {
            return static_cast<float>(this->m_value);
        }

        auto Number::getMin() -> double
        {
            log_trace(Log::Get);

            return this->m_min;
        }

        auto Number::getMax() -> double
        {
            log_trace(Log::Get);

            return this->m_max;
        }

        Number::~Number()
        {
            log_trace(Log::Del, this);
        }
    }
}