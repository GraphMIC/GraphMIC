#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Connection : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}