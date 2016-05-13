#pragma once

#include "gmViewerExport.hpp"

#include "mitkRenderingManagerFactory.h"

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT RenderingManagerFactory: public mitk::RenderingManagerFactory
        {
        public:
            RenderingManagerFactory();
            ~RenderingManagerFactory();
            
            virtual auto CreateRenderingManager() -> mitk::RenderingManager::Pointer const;
        };
    }
}
