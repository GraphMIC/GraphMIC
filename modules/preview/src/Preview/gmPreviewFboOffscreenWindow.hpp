#pragma once

#include "gmPreviewExport.hpp"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>

#include <vtkGenericOpenGLRenderWindow.h>

namespace gm
{
    namespace Preview
    {
        class FboRenderer;
        
        class GM_PREVIEW_EXPORT FboOffscreenWindow : public vtkGenericOpenGLRenderWindow
        {
        public:
            FboRenderer* QtParentRenderer;
            static auto New() -> FboOffscreenWindow*;
            virtual auto OpenGLInitState() -> void;
            auto Render() -> void;
            auto InternalRender() -> void;
            auto SetFramebufferObject(QOpenGLFramebufferObject*) -> void;
        protected:
            FboOffscreenWindow();
            ~FboOffscreenWindow();
        };
    }
}