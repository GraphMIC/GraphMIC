#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class GM_CORE_EXPORT Core : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
