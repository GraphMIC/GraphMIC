#pragma once

#include "gmDialogBase.hpp"

namespace gm
{
    namespace Dialog
    {
        class About : public Base
        {
        public:
            About();
            static About* instance;
            static auto Show() -> void;
        };
    }
}