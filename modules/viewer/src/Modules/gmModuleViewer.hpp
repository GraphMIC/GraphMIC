#pragma once

#include "gmViewerExport.hpp"
#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class GM_VIEWER_EXPORT Viewer : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
