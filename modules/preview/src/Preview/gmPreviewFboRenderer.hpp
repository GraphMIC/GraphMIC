#pragma once

#include "gmPreviewExport.hpp"

#include <QQuickFramebufferObject>
#include <QMouseEvent>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

namespace gm
{
    namespace Preview
    {
        class FboOffscreenWindow;
        
        class GM_PREVIEW_EXPORT FboRenderer : public QQuickFramebufferObject::Renderer
        {
            friend class FboOffscreenWindow;
        private:
            FboOffscreenWindow* m_fboOffscreenWindow;
            QOpenGLFramebufferObject* m_fbo;
        public:
            vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
            vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
        public:
            FboRenderer(FboOffscreenWindow*);
            auto synchronize(QQuickFramebufferObject*) -> void override;
            auto render() -> void override;
            auto onMouseEvent(QMouseEvent*) -> void;
            auto createFramebufferObject(const QSize&) -> QOpenGLFramebufferObject* override;
            ~FboRenderer();
        };
    }
}