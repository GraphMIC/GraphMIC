#pragma once

#include "gmPreviewExport.hpp"

#include "gmModuleBase.hpp"

namespace gm
{
    namespace Module
    {
        class GM_PREVIEW_EXPORT Preview : public Base
        {
        public:
            static auto Initialize() -> void;
        };
    }
}
