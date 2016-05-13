#pragma once

#include "gmLogicExport.hpp"

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class GM_LOGIC_EXPORT Logic : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}