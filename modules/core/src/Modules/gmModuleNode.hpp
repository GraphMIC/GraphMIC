#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Node : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}