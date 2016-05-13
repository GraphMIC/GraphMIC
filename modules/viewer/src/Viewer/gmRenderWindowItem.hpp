#pragma once

#include "gmViewerExport.hpp"

#include "QVTKQuickItem.h"

#include "mitkRenderWindowBase.h"

#include <vtkCornerAnnotation.h>
#include <vtkMitkRectangleProp.h>

namespace gm
{
    namespace ViewItem
    {
        class StdMultiItem;

        class GM_VIEWER_EXPORT RenderWindowItem: public QVTKQuickItem, public mitk::RenderWindowBase
        {
            Q_OBJECT
            Q_PROPERTY(int viewType READ getViewType WRITE setViewType NOTIFY viewTypeChanged);
            Q_PROPERTY(gm::ViewItem::StdMultiItem* multiItem READ getMultiItem WRITE setMultiItem NOTIFY multiItemChanged);
        private:
            vtkSmartPointer<vtkCornerAnnotation>    m_annotation;
            vtkSmartPointer<vtkMitkRectangleProp>   m_rectangle;
            StdMultiItem*   m_multiItem;
            int             m_viewType;
            bool            m_initialized;
        public:
            static RenderWindowItem* instance;
        public:
            RenderWindowItem(QQuickItem* parent = 0, const QString& name = "QML render window", mitk::VtkPropRenderer* renderer = NULL, mitk::RenderingManager* renderingManager = NULL);
            ~RenderWindowItem();
            auto setDataStorage(mitk::DataStorage::Pointer storage) -> void;
            auto createPlaneNode() -> void;
            auto setMultiItem(StdMultiItem* multiItem) -> void;
            auto getMultiItem() -> StdMultiItem*;
            auto setDecorationProperties(std::string text, mitk::Color color) -> void;
            auto setViewType(int type) -> void;
            auto getViewType() -> int;
            auto geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) -> void;
            virtual auto GetVtkRenderWindow() -> vtkRenderWindow* override;
            virtual auto GetVtkRenderWindowInteractor() -> vtkRenderWindowInteractor* override;
            virtual auto prepareForRender() -> bool;
            virtual auto cleanupAfterRender() -> void;
            virtual auto mousePressEvent(QMouseEvent* e) -> void;
            virtual auto mouseDoubleClickEvent(QMouseEvent *me) -> void;
            virtual auto mouseReleaseEvent(QMouseEvent* e) -> void;
            virtual auto mouseMoveEvent(QMouseEvent* e) -> void;
            virtual auto wheelEvent(QWheelEvent* e) -> void;
            virtual auto keyPressEvent(QKeyEvent *e) -> void;
            virtual auto hoverEnterEvent(QHoverEvent *e) -> void;
            auto GetMousePosition(QMouseEvent* me) -> mitk::Point2D const;
            auto GetMousePosition(QWheelEvent* we) -> mitk::Point2D const;
            auto GetEventButton(QMouseEvent* me) -> mitk::InteractionEvent::MouseButtons const;
            auto GetButtonState(QMouseEvent* me) -> mitk::InteractionEvent::MouseButtons const;
            auto GetModifiers(QInputEvent* me) -> mitk::InteractionEvent::ModifierKeys const;
            auto GetButtonState(QWheelEvent* we) -> mitk::InteractionEvent::MouseButtons const;
            auto GetKeyLetter(QKeyEvent *ke) -> std::string const;
            static auto GetInstanceForVTKRenderWindow( vtkRenderWindow* rw ) -> RenderWindowItem*;
            static auto GetInstances() -> QMap<vtkRenderWindow*, RenderWindowItem*>&;
        public slots:
            void setupView();
        signals:
            void multiItemChanged();
            void viewTypeChanged();
        };
    }
}
