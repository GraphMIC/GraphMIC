#pragma once

#include "gmPreviewExport.hpp"

#include <QQuickFramebufferObject>

#include <vtkImageSliceMapper.h>
#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>

class vtkGenericOpenGLRenderWindow;

namespace gm
{
    namespace Data
    {
        class Image;
    }

    namespace Slot
    {
        class OutputBase;
    }

    namespace Preview
    {
        class FboRenderer;
        
        class GM_PREVIEW_EXPORT ImageViewer : public QQuickFramebufferObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput WRITE setOutput NOTIFY outputChanged);
            Q_PROPERTY(gm::Data::Image* image READ getImage NOTIFY imageChanged);
            Q_PROPERTY(int stackIndex READ getStackIndex NOTIFY stackIndexChanged);
            Q_PROPERTY(int stackSize READ getStackSize NOTIFY stackSizeChanged);
        private:
            friend class FboRenderer;
            vtkSmartPointer<vtkRenderer> m_renderer;
            Slot::OutputBase* m_output;
            Data::Image* m_image;
            bool m_initialized;
            int m_stackIndex;
            int m_stackSize;
            auto setOutput(Slot::OutputBase*) -> void;
            auto getOutput() -> Slot::OutputBase*;
            auto setImage(Data::Image*) -> void;
            auto getImage() -> Data::Image*;
            auto setStackIndex(int) -> void;
            auto getStackIndex() -> int;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            auto updateData() -> void;
            auto set2DData(vtkSmartPointer<vtkImageData>) -> void;
            auto set3DData(vtkSmartPointer<vtkImageData>) -> void;
        public:
            ImageViewer();
            auto update() -> void;
            auto init() -> void;
            Renderer *createRenderer() const override;
            vtkGenericOpenGLRenderWindow* GetRenderWindow() const;
            ~ImageViewer();
        protected:
            mutable FboRenderer* m_fboRenderer;
            vtkGenericOpenGLRenderWindow *m_win;
            auto mousePressEvent(QMouseEvent*) -> void override;
            auto mouseReleaseEvent(QMouseEvent*) -> void override;
            auto mouseMoveEvent(QMouseEvent*) -> void override;
            auto hoverMoveEvent(QHoverEvent*) -> void override;
        public slots:
            void showImageInViewer();
        signals:
            void stackIndexChanged();
            void stackSizeChanged();
            void outputChanged();
            void imageChanged();
            void created();
        };
    }
}