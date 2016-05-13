#pragma once

#include "gmCoreExport.hpp"

#include "gmAppContextBase.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class GM_CORE_EXPORT Settings : public Base
            {
                Q_OBJECT
            private:
                Settings();
            public:
                static Settings* instance;
                static auto Create() -> Settings*;
                ~Settings();
            };
        }
    }
}