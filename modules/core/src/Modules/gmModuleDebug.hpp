#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Debug : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
