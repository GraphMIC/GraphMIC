#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Number : public Param
            {
                Q_OBJECT
                Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged);
                Q_PROPERTY(double min READ getMin WRITE setMin NOTIFY minChanged);
                Q_PROPERTY(double max READ getMax WRITE setMax NOTIFY maxChanged);
            private:
                double m_value;
                double m_min;
                double m_max;
            public:
                Number(Object*);
                auto setValue(double) -> void;
                auto getValue() -> double;
                auto setMin(double) -> void;
                auto getMin() -> double;
                auto setMax(double) -> void;
                auto getMax() -> double;
            signals:
                void valueChanged();
                void minChanged();
                void maxChanged();
            };
        }
    }
}