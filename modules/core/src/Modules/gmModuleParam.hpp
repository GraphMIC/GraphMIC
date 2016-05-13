#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Param : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}