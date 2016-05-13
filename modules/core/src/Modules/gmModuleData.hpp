#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Data : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}