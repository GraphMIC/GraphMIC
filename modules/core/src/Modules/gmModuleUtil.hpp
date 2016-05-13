#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Util : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
