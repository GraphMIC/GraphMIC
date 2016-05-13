#pragma once

#include "gmComponentBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT Base : public Component::Base
        {
            Q_OBJECT
        public:
            Base() = delete;
            Base(Component::Type, const QString&);
            virtual ~Base();
        };
    }
}
