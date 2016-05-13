#pragma once

#include "gmCoreExport.hpp"

#include "gmAppContextBase.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class GM_CORE_EXPORT Viewer : public Base
            {
                Q_OBJECT
            private:
                Viewer();
            public:
                static Viewer* instance;
                static auto Create() -> Viewer*;
                ~Viewer();
            };
        }
    }
}