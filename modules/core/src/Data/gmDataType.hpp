#pragma once

#include "gmCoreExport.hpp"

namespace gm
{
    namespace Data
    {
        enum class Type
        {
            Image = 0,
            Number,
            Vector,
            Pointset
        };

        auto GM_CORE_EXPORT TypeFromIndex(int) -> Type;
        auto GM_CORE_EXPORT TypeToIndex(Type) -> int;
        auto GM_CORE_EXPORT TypeToString(Type) -> QString;
    }
}
