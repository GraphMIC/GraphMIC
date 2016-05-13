#pragma once

#include "gmDialogBase.hpp"

namespace gm
{
    namespace Dialog
    {
        class Settings : public Base
        {
        public:
            Settings();
            static Settings* instance;
            static auto Show() -> void;
        };
    }
}