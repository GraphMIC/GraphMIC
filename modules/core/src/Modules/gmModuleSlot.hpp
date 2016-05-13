#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Slot : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}