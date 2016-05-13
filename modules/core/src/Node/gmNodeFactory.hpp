#pragma once

#include "gmCoreExport.hpp"

#include <QString>

namespace gm
{
    namespace Node
    {
        class Object;
        
        class GM_CORE_EXPORT Factory
        {
        public:
            static auto Create(const QString&) -> Object*;
        };
    }
}