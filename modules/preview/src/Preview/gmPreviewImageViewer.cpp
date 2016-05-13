#include "gmLog.hpp"

#include "gmAsync.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmDataImage.hpp"
#include "gmPreviewImageViewer.hpp"
#include "gmPreviewController.hpp"
#include "gmPreviewFboRenderer.hpp"
#include "gmPreviewFboOffscreenWindow.hpp"
#include "gmInterfaceViewerController.hpp"

#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QSGTransformNode>
#include <QSGSimpleTextureNode>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkRendererCollection.h>
#include <vtkImageSliceMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper.h>
#include <vtkImageActor.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkCommand.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkActor.h>

namespace gm
{
    namespace Preview
    {
        ImageViewer::ImageViewer() : m_initialized(false)
        {
            log_trace(Log::New, this);
            
            this->m_renderer    = nullptr;
            this->m_output      = nullptr;
            this->m_image       = nullptr;
            this->m_stackIndex  = 0;
            this->m_stackSize   = 0;
            
            m_win = FboOffscreenWindow::New();
            setAcceptHoverEvents(true);
            setAcceptedMouseButtons(Qt::AllButtons);

            this->setMirrorVertically(false);

            QObject::connect(Preview::Controller::instance, &Preview::Controller::stackIndexChanged, this, [this](){
                this->setStackIndex(Preview::Controller::instance->getStackIndex());
            });
        }
        
        auto ImageViewer::init() -> void
        {
            log_trace(Log::Func);

            this->m_renderer = vtkSmartPointer<vtkRenderer>::New();
            this->m_win->AddRenderer(m_renderer);
            this->m_initialized = true;

            emit this->created();
            
            if (!this->m_output)
            {
                return;
            }

            if (this->m_output)
            {
                if (this->m_output->getDataCount() > 0)
                {
                    auto data = this->m_output->getData(0);

                    if (data)
                    {
                        this->setImage(data->as<Data::Image>());
                    }
                }
            }
        }

        auto ImageViewer::setStackIndex(int stackIndex) -> void
        {
            log_trace(Log::Set, stackIndex);

            if (this->m_stackIndex != stackIndex)
            {
                this->m_stackIndex = stackIndex;
                emit this->stackIndexChanged();

                this->updateData();
            }
        }

        auto ImageViewer::getStackIndex() -> int
        {
            return this->m_stackIndex;
        }

        auto ImageViewer::setStackSize(int stackSize) -> void
        {
            log_trace(Log::Set, stackSize);

            if (this->m_stackSize != stackSize)
            {
                this->m_stackSize = stackSize;
                emit this->stackSizeChanged();
            }
        }

        auto ImageViewer::getStackSize() -> int
        {
            return this->m_stackSize;
        }

        auto ImageViewer::updateData() -> void
        {
            log_trace(Log::Func);

            if (this->m_output)
            {
                this->setStackSize(this->m_output->getDataCount());

                if (this->m_stackIndex >= this->m_output->getDataCount() && this->m_output->getDataCount() > 0)
                {
                    setStackIndex(0);
                }
                else
                {
                    auto data = this->m_output->getData(this->m_stackIndex);

                    if (data)
                    {
                        this->setImage(data->as<Data::Image>());
                    }
                }
            }
            else
            {
                this->setStackSize(0);
            }
        }

        auto ImageViewer::setOutput(Slot::OutputBase* output) -> void
        {
            log_trace(Log::Set, output);

            if (this->m_output == output)
            {
                return;
            }

            this->m_output = output;
            emit this->outputChanged();

            if (output)
            {
                QObject::connect(output, &Slot::OutputBase::dataChanged, this, [this](){
                    this->updateData();
                });
            }

            this->updateData();
        }

        auto ImageViewer::getOutput() -> Slot::OutputBase*
        {
            return this->m_output;
        }

        auto ImageViewer::setImage(Data::Image* image) -> void
        {
            log_trace(Log::Set);

            if (this->m_image != image)
            {
                this->m_image = image;
                emit this->imageChanged();
            }

            if (image)
            {
                Async::Synchronize([image, this](){
                    auto mitkImage = image->getMitkImage();

                    if (image->getDimension() == 2)
                    {
                        this->set2DData(mitkImage->GetVtkImageData());
                    }
                    else
                    {
                        this->set3DData(mitkImage->GetVtkImageData());
                    }
                });
            }
        }

        auto ImageViewer::getImage() -> Data::Image*
        {
            return this->m_image;
        }
        
        auto ImageViewer::set2DData(vtkSmartPointer<vtkImageData> imageData) -> void
        {
            log_trace(Log::Func, imageData);
            log_info("imagedata: " << imageData);
            log_info("initialized: " << m_initialized);

            if (this->m_initialized)
            {
                this->m_renderer->RemoveAllViewProps();

                auto actor  = vtkSmartPointer<vtkImageActor>::New();
                auto mapper = vtkSmartPointer<vtkImageSliceMapper>::New();
            
                actor->SetMapper(mapper);
                mapper->SetInputData(imageData);
            
                this->m_renderer->AddActor(actor);
                this->m_renderer->ResetCamera();
                this->update();
            }
        }
        
        auto ImageViewer::set3DData(vtkSmartPointer<vtkImageData> imageData) -> void
        {
            log_trace(Log::Func, imageData);
            
            if (this->m_initialized)
            {
                this->m_renderer->RemoveAllViewProps();
                
                auto actor  = vtkSmartPointer<vtkVolume>::New();
                auto mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
                
                actor->SetMapper(mapper);
                mapper->SetInputData(imageData);
                
                this->m_renderer->AddActor(actor);
                this->m_renderer->ResetCamera();
                this->update();   
            }            
        }

        auto ImageViewer::showImageInViewer() -> void
        {
            log_trace(Log::Func);

            if (this->m_image)
            {
                Interface::Viewer::Controller::instance->addImage(this->m_image);
            }
        }

        auto ImageViewer::update() -> void
        {
            if (!this->m_initialized)
            {
                return;
            }
            
            if (this->m_fboRenderer)
            {
                QQuickFramebufferObject::update();
            }
        }
        
        auto ImageViewer::mousePressEvent(QMouseEvent* event) -> void
        {
            if (this->m_fboRenderer)
            {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }
        auto ImageViewer::mouseReleaseEvent(QMouseEvent* event) -> void
        {
            if (this->m_fboRenderer)
            {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }
        
        auto ImageViewer::mouseMoveEvent(QMouseEvent* event) -> void
        {
            if (this->m_fboRenderer)
            {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }
        
        auto ImageViewer::hoverMoveEvent(QHoverEvent* event) -> void
        {
        }
        
        auto ImageViewer::createRenderer() const -> QQuickFramebufferObject::Renderer*
        {
            this->m_fboRenderer = new FboRenderer(static_cast<FboOffscreenWindow*>(m_win));
            
            return this->m_fboRenderer;
        }
        
        auto ImageViewer::GetRenderWindow() const -> vtkGenericOpenGLRenderWindow*
        {
            return m_win;
        }
        
        ImageViewer::~ImageViewer()
        {
            log_trace(Log::Del, this);
            
            m_win->Delete();
        }
    }
}
