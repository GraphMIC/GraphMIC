#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Slot
    {
        template <class T> class Output;
    }

    namespace Data
    {
        class Number;
    };

    namespace Param
    {
        class GM_CORE_EXPORT Number : public Base
        {
            Q_OBJECT
            Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged);
            Q_PROPERTY(double min READ getMin CONSTANT);
            Q_PROPERTY(double max READ getMax CONSTANT);
        private:
            Slot::Output<Data::Number>* m_output;
            double m_value;
            double m_min;
            double m_max;
        public:
            static Component::Type ComponentType;
            Number(const QString& name, double, double, double);
            Number(const QString& name, double);
            Number(const QString& name);
            auto link(Slot::Output<Data::Number>*) -> void;
            auto setValue(double) -> void;
            auto getValue() -> double;
            auto getIntValue() -> int;
            auto getFloatValue() -> float;
            auto getMin() -> double;
            auto getMax() -> double;
            ~Number();
        signals:
            void valueChanged();
        };
    }
}