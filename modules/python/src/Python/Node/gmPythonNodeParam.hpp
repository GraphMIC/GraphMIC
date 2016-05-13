#pragma once

#include "gmPythonNodeComponent.hpp"

#include <QObject>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Param : public Component
            {
                Q_OBJECT
            private:
            public:
                Param(gm::Component::Type, Object*);
            };
        }
    }
}