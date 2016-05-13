#pragma once

#include "gmCoreExport.hpp"

namespace gm
{
    namespace Slot
    {
        enum class Type
        {
            Input,
            Output
        };

        auto GM_CORE_EXPORT TypeFromIndex(int) -> Type;
    }
}
