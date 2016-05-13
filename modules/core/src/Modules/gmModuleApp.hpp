#pragma once

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class App : public Module::Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
