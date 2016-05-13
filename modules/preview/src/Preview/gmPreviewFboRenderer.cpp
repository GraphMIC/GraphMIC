#include "gmLog.hpp"

#include "gmPreviewFboRenderer.hpp"
#include "gmPreviewFboOffscreenWindow.hpp"
#include "gmPreviewImageViewer.hpp"

#include <vtkRendererCollection.h>
#include <vtkCommand.h>
#include <vtkCamera.h>

namespace gm
{
    namespace Preview
    {
        FboRenderer::FboRenderer(FboOffscreenWindow *offscreenWindow) : m_fboOffscreenWindow(offscreenWindow), m_fbo(0)
        {
            log_trace(Log::Func);
            
            m_fboOffscreenWindow->Register(NULL);
            m_fboOffscreenWindow->QtParentRenderer = this;
            
            m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
            m_interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
            
            m_interactor->SetRenderWindow(offscreenWindow);
            m_interactor->Initialize();
            m_interactor->SetInteractorStyle(m_interactorStyle);
        }
        
        auto FboRenderer::synchronize(QQuickFramebufferObject* fbo) -> void
        {
            if (!m_fbo)
            {
                auto viewer = static_cast<ImageViewer*>(fbo);
                viewer->init();
            }
        }
        
        auto FboRenderer::render() -> void
        {
            m_fboOffscreenWindow->PushState();
            m_fboOffscreenWindow->OpenGLInitState();
            m_fboOffscreenWindow->InternalRender();
            m_fboOffscreenWindow->PopState();
        }
        
        auto FboRenderer::createFramebufferObject(const QSize &size) -> QOpenGLFramebufferObject*
        {            
            QOpenGLFramebufferObjectFormat format;
            format.setAttachment(QOpenGLFramebufferObject::Depth);
            m_fbo = new QOpenGLFramebufferObject(size, format);
            m_fboOffscreenWindow->SetFramebufferObject(m_fbo);
            
            return m_fbo;
        }
        
        auto FboRenderer::onMouseEvent(QMouseEvent* event) -> void
        {
            if(this->m_interactor == NULL || event == NULL)
                return;
            
            if(!this->m_interactor->GetEnabled())
                return;
  
            this->m_interactor->SetEventInformation(event->x(), event->y(), (event->modifiers() & Qt::ControlModifier) > 0 ? 1 : 0, (event->modifiers() & Qt::ShiftModifier ) > 0 ? 1 : 0, 0, event->type() == QEvent::MouseButtonDblClick ? 1 : 0);
            
            auto command = vtkCommand::NoEvent;
            
            if (event->type() == QEvent::MouseMove)
                command = vtkCommand::MouseMoveEvent;
                
                else if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
                {
                    switch (event->button())
                    {
                        case Qt::LeftButton:    command = vtkCommand::LeftButtonPressEvent; break;
                        case Qt::RightButton:   command = vtkCommand::RightButtonPressEvent; break;
                        case Qt::MidButton:     command = vtkCommand::MiddleButtonPressEvent; break;
                        default: break;
                    }
                }
            
                else if (event->type() == QEvent::MouseButtonRelease)
                {
                    switch (event->button())
                    {
                        case Qt::LeftButton:    command = vtkCommand::LeftButtonReleaseEvent; break;
                        case Qt::RightButton:   command = vtkCommand::RightButtonReleaseEvent; break;
                        case Qt::MidButton:     command = vtkCommand::MiddleButtonReleaseEvent; break;
                        default: break;
                    }
                }
            
            this->m_interactor->InvokeEvent(command, event);
        }
        
        FboRenderer::~FboRenderer()
        {
            log_trace(Log::Del, this);
            
            m_fboOffscreenWindow->QtParentRenderer = 0;
            m_fboOffscreenWindow->Delete();
        }
    };
}