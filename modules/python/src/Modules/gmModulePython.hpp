#pragma once

#include "gmPythonExport.hpp"

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class GM_PYTHON_EXPORT Python : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
