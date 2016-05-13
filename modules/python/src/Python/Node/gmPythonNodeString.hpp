#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class String : public Param
            {
                Q_OBJECT
                Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged);
            private:
                QString m_value;
            public:
                String(Object*);
                auto setValue(const QString&) -> void;
                auto getValue() -> QString;
            signals:
                void valueChanged();
            };
        }
    }
}