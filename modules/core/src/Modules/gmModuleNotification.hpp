#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class Notification : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}