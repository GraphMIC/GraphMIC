/*===================================================================

 The Medical Imaging Interaction Toolkit (MITK)

 Copyright (c) German Cancer Research Center,
 Division of Medical and Biological Informatics.
 All rights reserved.

 This software is distributed WITHOUT ANY WARRANTY; without
 even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.

 See LICENSE.txt or http://www.mitk.org for details.

 ===================================================================*/
#define US_MODULE_NAME GraphMic
#include "gmRenderWindowItem.hpp"

#include <QVTKInteractor.h>
#include <QVTKInteractorAdapter.h>

#include <vtkEventQtSlotConnect.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkTextProperty.h>

#include "mitkMouseWheelEvent.h"
#include "mitkMousePressEvent.h"
#include "mitkMouseMoveEvent.h"
#include "mitkMouseDoubleClickEvent.h"
#include "mitkMouseReleaseEvent.h"
#include "mitkInteractionKeyEvent.h"
#include "mitkInternalEvent.h"
#include "mitkCameraController.h"
#include "mitkPlaneGeometryDataMapper2D.h"

#include "gmStdMultiItem.hpp"
#include <QQuickWindow>

namespace gm
{
    namespace ViewItem
    {

        RenderWindowItem* RenderWindowItem::instance = nullptr;

        RenderWindowItem* RenderWindowItem::GetInstanceForVTKRenderWindow(vtkRenderWindow* rw)
        {
            if (GetInstances().contains(rw))
            {
                return GetInstances()[rw];
            }
            return 0;
        }

        auto RenderWindowItem::GetInstances() -> QMap<vtkRenderWindow*, RenderWindowItem*>&
        {
            static QMap<vtkRenderWindow*, RenderWindowItem*> s_Instances;
            return s_Instances;
        }

        RenderWindowItem::RenderWindowItem(QQuickItem* parent, const QString& name, mitk::VtkPropRenderer* , mitk::RenderingManager* renderingManager) : QVTKQuickItem(parent), m_initialized(false)
        {
            instance = this;

            mitk::RenderWindowBase::Initialize(renderingManager, name.toStdString().c_str());
            GetInstances()[QVTKQuickItem::GetRenderWindow()] = this;

            this->m_annotation = vtkSmartPointer<vtkCornerAnnotation>::New();
            this->m_rectangle  = vtkSmartPointer<vtkMitkRectangleProp>::New();
        }

        auto RenderWindowItem::createPlaneNode() -> void
        {
            mitk::DataStorage::Pointer m_DataStorage = mitk::RenderWindowBase::GetRenderer()->GetDataStorage();
            if (m_DataStorage.IsNotNull())
            {
                mitk::RenderingManager::GetInstance()->InitializeViews( m_DataStorage->ComputeBoundingGeometry3D(m_DataStorage->GetAll()) );
            }

            if (this->GetRenderer()->GetSliceNavigationController()->GetDefaultViewDirection() == mitk::SliceNavigationController::Original)
                return;

            mitk::DataNode::Pointer		planeNode;
            mitk::IntProperty::Pointer  layer;
            mitk::PlaneGeometryDataMapper2D::Pointer mapper = mitk::PlaneGeometryDataMapper2D::New();

            layer = mitk::IntProperty::New(1000);

            planeNode = this->GetRenderer()->GetCurrentWorldPlaneGeometryNode();

            planeNode->SetProperty("visible", mitk::BoolProperty::New(true));
            planeNode->SetProperty("name", mitk::StringProperty::New("plane"));
            planeNode->SetProperty("isPlane", mitk::BoolProperty::New(true));
            planeNode->SetProperty("includeInBoundingBox", mitk::BoolProperty::New(false));
            planeNode->SetProperty("helper object", mitk::BoolProperty::New(true));
            planeNode->SetProperty("layer", layer);
            planeNode->SetMapper(mitk::BaseRenderer::Standard2D, mapper);

            switch (this->GetRenderer()->GetSliceNavigationController()->GetDefaultViewDirection())
            {
                case mitk::SliceNavigationController::Axial:
                    planeNode->SetColor(0.88, 0.35, 0.27);
                    break;
                case mitk::SliceNavigationController::Sagittal:
                    planeNode->SetColor(0.25, 0.7, 0.35);
                    break;
                case mitk::SliceNavigationController::Frontal:
                    planeNode->SetColor(0.01, 0.31, 0.67);
                    break;
                default:
                    planeNode->SetColor(1.0, 1.0, 0.0);
            }

        }

        auto RenderWindowItem::setViewType(int viewType) -> void
        {
            this->m_viewType = viewType;

            emit this->viewTypeChanged();
        }

        auto RenderWindowItem::setDecorationProperties(std::string text, mitk::Color color) -> void
        {
            this->m_annotation->SetText(0, text.c_str());
            this->m_annotation->SetMaximumFontSize(12);
            this->m_annotation->GetTextProperty()->SetColor( color[0],color[1],color[2] );


            if(!this->GetRenderer()->GetVtkRenderer()->HasViewProp(this->m_annotation))
            {
                this->GetRenderer()->GetVtkRenderer()->AddViewProp(this->m_annotation);
            }

            this->m_rectangle->SetColor(color[0],color[1],color[2]);

            if(!this->GetRenderer()->GetVtkRenderer()->HasViewProp(this->m_rectangle))
            {
                this->GetRenderer()->GetVtkRenderer()->AddViewProp(this->m_rectangle);
            }
        }

        auto RenderWindowItem::setupView() -> void
        {
            switch (this->m_viewType)
            {
                case 0:
                    this->GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard2D);
                    this->GetRenderer()->GetSliceNavigationController()->SetDefaultViewDirection(mitk::SliceNavigationController::Axial);
                    break;
                case 1:
                    this->GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard2D);
                    this->GetRenderer()->GetSliceNavigationController()->SetDefaultViewDirection(mitk::SliceNavigationController::Frontal);
                    break;
                case 2:
                    this->GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard2D);
                    this->GetRenderer()->GetSliceNavigationController()->SetDefaultViewDirection(mitk::SliceNavigationController::Sagittal);
                    break;
                case 3:
                    this->GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard3D);
                    this->GetRenderer()->GetSliceNavigationController()->SetDefaultViewDirection(mitk::SliceNavigationController::Original);
                    break;
                default:
                    break;
            }
        }

        auto RenderWindowItem::setMultiItem(StdMultiItem* multiItem) -> void
        {
            if(this->m_multiItem == multiItem)
                return;

            this->m_multiItem = multiItem;
            this->m_multiItem->registerViewerItem(this);
        }

        auto RenderWindowItem::getMultiItem() -> StdMultiItem*
        {
            return this->m_multiItem;
        }

        auto RenderWindowItem::setDataStorage(mitk::DataStorage::Pointer storage) -> void
        {
            this->GetRenderer()->SetDataStorage(storage);
        }

        auto RenderWindowItem::GetMousePosition(QMouseEvent* me) -> mitk::Point2D const
        {
            qreal ratio = this->window()->effectiveDevicePixelRatio();
            mitk::Point2D point;
            point[0] = me->x()*ratio;
            point[1] = me->y()*ratio;
            return point;
        }

        auto RenderWindowItem::GetMousePosition(QWheelEvent* we) -> mitk::Point2D const
        {
            qreal ratio = this->window()->effectiveDevicePixelRatio();
            mitk::Point2D point;
            point[0] = we->x()*ratio;
            point[1] = we->y()*ratio;
            return point;
        }

        auto RenderWindowItem::GetEventButton(QMouseEvent* me) -> mitk::InteractionEvent::MouseButtons const
        {
            mitk::InteractionEvent::MouseButtons eventButton;
            switch (me->button())
            {
                case Qt::LeftButton:
                    eventButton = mitk::InteractionEvent::LeftMouseButton;
                    break;
                case Qt::RightButton:
                    eventButton = mitk::InteractionEvent::RightMouseButton;
                    break;
                case Qt::MidButton:
                    eventButton = mitk::InteractionEvent::MiddleMouseButton;
                    break;
                default:
                    eventButton = mitk::InteractionEvent::NoButton;
                    break;
            }
            return eventButton;
        }

        auto RenderWindowItem::GetButtonState(QMouseEvent* me) -> mitk::InteractionEvent::MouseButtons const
        {
            mitk::InteractionEvent::MouseButtons buttonState = mitk::InteractionEvent::NoButton;

            if (me->buttons() & Qt::LeftButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::LeftMouseButton;
            }
            if (me->buttons() & Qt::RightButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::RightMouseButton;
            }
            if (me->buttons() & Qt::MidButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::MiddleMouseButton;
            }
            return buttonState;
        }

        auto RenderWindowItem::GetModifiers(QInputEvent* me) -> mitk::InteractionEvent::ModifierKeys const
        {
            mitk::InteractionEvent::ModifierKeys modifiers = mitk::InteractionEvent::NoKey;

            if (me->modifiers() & Qt::ALT)
            {
                modifiers = modifiers | mitk::InteractionEvent::AltKey;
            }
            if (me->modifiers() & Qt::CTRL)
            {
                modifiers = modifiers | mitk::InteractionEvent::ControlKey;
            }
            if (me->modifiers() & Qt::SHIFT)
            {
                modifiers = modifiers | mitk::InteractionEvent::ShiftKey;
            }
            return modifiers;
        }

        auto RenderWindowItem::GetButtonState(QWheelEvent* we) -> mitk::InteractionEvent::MouseButtons const
        {
            mitk::InteractionEvent::MouseButtons buttonState = mitk::InteractionEvent::NoButton;

            if (we->buttons() & Qt::LeftButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::LeftMouseButton;
            }
            if (we->buttons() & Qt::RightButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::RightMouseButton;
            }
            if (we->buttons() & Qt::MidButton)
            {
                buttonState = buttonState | mitk::InteractionEvent::MiddleMouseButton;
            }
            return buttonState;
        }

        auto RenderWindowItem::GetKeyLetter(QKeyEvent *ke) -> std::string const
        {

            std::string key = "";
            int tkey = ke->key();
            if (tkey < 128)
            {
                key = (char)toupper(tkey);
            }
            else
            {
                switch (tkey)
                {
                    case Qt::Key_Return:
                        key = mitk::InteractionEvent::KeyReturn;
                        break;
                    case Qt::Key_Enter:
                        key = mitk::InteractionEvent::KeyEnter;
                        break;
                    case Qt::Key_Escape:
                        key = mitk::InteractionEvent::KeyEsc;
                        break;
                    case Qt::Key_Delete:
                        key = mitk::InteractionEvent::KeyDelete;
                        break;
                    case Qt::Key_Up:
                        key = mitk::InteractionEvent::KeyArrowUp;
                        break;
                    case Qt::Key_Down:
                        key = mitk::InteractionEvent::KeyArrowDown;
                        break;
                    case Qt::Key_Left:
                        key = mitk::InteractionEvent::KeyArrowLeft;
                        break;
                    case Qt::Key_Right:
                        key = mitk::InteractionEvent::KeyArrowRight;
                        break;
                    case Qt::Key_F1:
                        key = mitk::InteractionEvent::KeyF1;
                        break;
                    case Qt::Key_F2:
                        key = mitk::InteractionEvent::KeyF2;
                        break;
                    case Qt::Key_F3:
                        key = mitk::InteractionEvent::KeyF3;
                        break;
                    case Qt::Key_F4:
                        key = mitk::InteractionEvent::KeyF4;
                        break;
                    case Qt::Key_F5:
                        key = mitk::InteractionEvent::KeyF5;
                        break;
                    case Qt::Key_F6:
                        key = mitk::InteractionEvent::KeyF6;
                        break;
                    case Qt::Key_F7:
                        key = mitk::InteractionEvent::KeyF7;
                        break;
                    case Qt::Key_F8:
                        key = mitk::InteractionEvent::KeyF8;
                        break;
                    case Qt::Key_F9:
                        key = mitk::InteractionEvent::KeyF9;
                        break;
                    case Qt::Key_F10:
                        key = mitk::InteractionEvent::KeyF10;
                        break;
                    case Qt::Key_F11:
                        key = mitk::InteractionEvent::KeyF11;
                        break;
                    case Qt::Key_F12:
                        key = mitk::InteractionEvent::KeyF12;
                        break;

                    case Qt::Key_End:
                        key = mitk::InteractionEvent::KeyEnd;
                        break;
                    case Qt::Key_Home:
                        key = mitk::InteractionEvent::KeyPos1;
                        break;
                    case Qt::Key_Insert:
                        key = mitk::InteractionEvent::KeyInsert;
                        break;
                    case Qt::Key_PageDown:
                        key = mitk::InteractionEvent::KeyPageDown;
                        break;
                    case Qt::Key_PageUp:
                        key = mitk::InteractionEvent::KeyPageUp;
                        break;
                    case Qt::Key_Space:
                        key = mitk::InteractionEvent::KeySpace;
                        break;
                    default:
                        break;
                }
            }
            return key;
        }

        auto RenderWindowItem::getViewType() -> int
        {
            return this->m_viewType;
        }

        auto RenderWindowItem::mousePressEvent(QMouseEvent* me) -> void
        {
            mitk::Point2D mousePosition = GetMousePosition(me);
            mousePosition[1] = this->GetRenderer()->GetSizeY() - mousePosition[1];

            mitk::MousePressEvent::Pointer mPressEvent =
            mitk::MousePressEvent::New(mitk::RenderWindowBase::GetRenderer(), mousePosition, GetButtonState(me), GetModifiers(me), GetEventButton(me));

            mitk::RenderWindowBase::HandleEvent(mPressEvent.GetPointer());
            QVTKQuickItem::mousePressEvent(me);
        }

        auto RenderWindowItem::mouseReleaseEvent(QMouseEvent* me) -> void
        {
            mitk::Point2D mousePosition = GetMousePosition(me);
            mousePosition[1] = this->GetRenderer()->GetSizeY() - mousePosition[1];

            mitk::MouseReleaseEvent::Pointer mReleaseEvent =
            mitk::MouseReleaseEvent::New(mitk::RenderWindowBase::GetRenderer(), mousePosition, GetButtonState(me), GetModifiers(me), GetEventButton(me));

            mitk::RenderWindowBase::HandleEvent(mReleaseEvent.GetPointer());
            QVTKQuickItem::mouseReleaseEvent(me);
        }

        auto RenderWindowItem::mouseMoveEvent(QMouseEvent* me) -> void
        {
            mitk::Point2D mousePosition = GetMousePosition(me);
            mousePosition[1] = this->GetRenderer()->GetSizeY() - mousePosition[1];

            mitk::MouseMoveEvent::Pointer mMoveEvent =
            mitk::MouseMoveEvent::New(mitk::RenderWindowBase::GetRenderer(), mousePosition, GetButtonState(me), GetModifiers(me));

            mitk::RenderWindowBase::HandleEvent(mMoveEvent.GetPointer());
            QVTKQuickItem::mouseMoveEvent(me);
        }

        auto RenderWindowItem::wheelEvent(QWheelEvent *we) -> void
        {
            mitk::Point2D mousePosition = GetMousePosition(we);

            mitk::MouseWheelEvent::Pointer mWheelEvent =
            mitk::MouseWheelEvent::New(mitk::RenderWindowBase::GetRenderer(), mousePosition, GetButtonState(we), GetModifiers(we), we->delta());

            mitk::RenderWindowBase::HandleEvent(mWheelEvent.GetPointer());
            QVTKQuickItem::wheelEvent(we);
        }

        auto RenderWindowItem::keyPressEvent(QKeyEvent *e) -> void
        {
            mitk::InteractionEvent::ModifierKeys modifiers = GetModifiers(e);
            std::string key = GetKeyLetter(e);

            mitk::InteractionKeyEvent::Pointer keyEvent = mitk::InteractionKeyEvent::New(m_Renderer, key, modifiers);
            if (!this->HandleEvent(keyEvent.GetPointer()))
            {
                QVTKQuickItem::keyPressEvent(e);
            }
        }

        auto RenderWindowItem::mouseDoubleClickEvent( QMouseEvent *me ) -> void
        {
            mitk::Point2D displayPos = GetMousePosition(me);
            mitk::MouseDoubleClickEvent::Pointer mPressEvent = mitk::MouseDoubleClickEvent::New(m_Renderer,displayPos, GetButtonState(me),GetModifiers(me), GetEventButton(me));

            if (!this->HandleEvent(mPressEvent.GetPointer()))
            {
                QVTKQuickItem::mousePressEvent(me);
            }
        }

        auto RenderWindowItem::hoverEnterEvent(QHoverEvent *e) -> void
        {
            forceActiveFocus();
            QVTKQuickItem::hoverEnterEvent(e);
        }

        auto RenderWindowItem::prepareForRender() -> bool
        {
            mitk::VtkPropRenderer *vPR = dynamic_cast<mitk::VtkPropRenderer*>(mitk::BaseRenderer::GetInstance(this->GetRenderWindow()));
            if (vPR)
            {
                vPR->PrepareRender();

                if(!m_initialized)
                {
                    mitk::BaseRenderer::GetInstance(this->GetRenderWindow())->GetCameraController()->Fit();
                    m_initialized = true;
                }
            }

            return true;
        }

        auto RenderWindowItem::cleanupAfterRender() -> void
        {
        }

        auto RenderWindowItem::geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) -> void
        {
            QVTKQuickItem::geometryChanged(newGeometry, oldGeometry);
            mitk::BaseRenderer::GetInstance(this->GetRenderWindow())->GetCameraController()->Fit();
        }

        RenderWindowItem::~RenderWindowItem()
        {
            this->Destroy();
        }

        auto RenderWindowItem::GetVtkRenderWindow() -> vtkRenderWindow*
        {
            return QVTKQuickItem::GetRenderWindow();
        }

        auto RenderWindowItem::GetVtkRenderWindowInteractor() -> vtkRenderWindowInteractor*
        {
            return QVTKQuickItem::GetInteractor();
        }
    }
}

