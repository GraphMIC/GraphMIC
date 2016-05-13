#pragma once

#include "gmCoreExport.hpp"

#include "gmAppContextBase.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class GM_CORE_EXPORT Python : public Base
            {
                Q_OBJECT
            private:
                Python();
            public:
                static Python* instance;
                static auto Create() -> Python*;
                ~Python();
            };
        }
    }
}