#pragma once

#include "gmCoreExport.hpp"

#include "gmAppContextBase.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class GM_CORE_EXPORT Graph : public Base
            {
                Q_OBJECT
            private:
                Graph();
            public:
                static Graph* instance;
                static auto Create() -> Graph*;
                ~Graph();
            };
        }
    }
}