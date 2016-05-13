#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Bool : public Param
            {
                Q_OBJECT
                Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged);
            private:
                bool m_value;
            public:
                Bool(Object*);
                auto setValue(bool) -> void;
                auto getValue() -> bool;
            signals:
                void valueChanged();
            };
        }
    }
}