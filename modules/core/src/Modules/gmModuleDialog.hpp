#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Dialog : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}