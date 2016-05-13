#pragma once

#include "gmCoreExport.hpp"

#include <QMetaType>

namespace gm
{
    namespace Component
    {
        enum class Type
        {
            Input   = 0,
            Output  = 1,
            Bool    = 2,
            Number  = 3,
            String  = 4,
            Option  = 5,
            Dir     = 6,
            Files   = 7,
            Vector  = 8
        };
        
        GM_CORE_EXPORT auto StringFromType(Type) -> QString;
    }
}

Q_DECLARE_METATYPE(gm::Component::Type);