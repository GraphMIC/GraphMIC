#include "gmStdMultiItem.hpp"
#include "gmRenderWindowItem.hpp"

#include <mitkImage.h>
#include <mitkIOUtil.h>
#include <mitkStandaloneDataStorage.h>
#include <mitkLine.h>

namespace gm
{
    namespace ViewItem
    {
        StdMultiItem* StdMultiItem::instance = nullptr;
        
        StdMultiItem::StdMultiItem() : m_mouseMode(0)
        {
            instance = this;
        }
        
        StdMultiItem::~StdMultiItem()
        {
        }
        
        auto StdMultiItem::registerViewerItem(RenderWindowItem*viewerItem) -> void
        {
            viewerItem->setupView();
            viewerItem->createPlaneNode();
            
            switch (viewerItem->GetRenderer()->GetSliceNavigationController()->GetDefaultViewDirection())
            {
                case mitk::SliceNavigationController::Axial:
                    this->m_viewerAxial = viewerItem;
                    break;
                case mitk::SliceNavigationController::Frontal:
                    this->m_viewerFrontal = viewerItem;
                    break;
                case mitk::SliceNavigationController::Sagittal:
                    this->m_viewerSagittal = viewerItem;
                    break;
                default:
                    this->m_viewerOriginal = viewerItem;
            }
        }
        
        void StdMultiItem::init()
        {
            if(StdMultiItem::storage.IsNull())
                StdMultiItem::storage = mitk::StandaloneDataStorage::New();
            
            this->m_mouseModeSwitcher = mitk::MouseModeSwitcher::New();

            this->m_viewerAxial->setDataStorage(StdMultiItem::storage);
            this->m_viewerFrontal->setDataStorage(StdMultiItem::storage);
            this->m_viewerSagittal->setDataStorage(StdMultiItem::storage);
            this->m_viewerOriginal->setDataStorage(StdMultiItem::storage);
            
            this->addPlanes();
            
            mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(StdMultiItem::storage);
        }
        
        auto StdMultiItem::getMouseMode() -> int
        {
            return this->m_mouseMode;
        }
        
        auto StdMultiItem::setMouseMode(int mode) -> void
        {
            this->m_mouseMode = mode;
            switch (this->m_mouseMode)
            {
                case 0:
                    this->m_mouseModeSwitcher->SetInteractionScheme(mitk::MouseModeSwitcher::InteractionScheme::MITK);
                    break;
                case 1:
                    this->m_mouseModeSwitcher->SetInteractionScheme(mitk::MouseModeSwitcher::InteractionScheme::ROTATION);
                    break;
                case 2:
                    this->m_mouseModeSwitcher->SetInteractionScheme(mitk::MouseModeSwitcher::InteractionScheme::ROTATIONLINKED);
                    break;
                case 3:
                    this->m_mouseModeSwitcher->SetInteractionScheme(mitk::MouseModeSwitcher::InteractionScheme::SWIVEL);
                    break;
                default:
                    this->m_mouseModeSwitcher->SetInteractionScheme(mitk::MouseModeSwitcher::InteractionScheme::MITK);
            }
        }
        
        void StdMultiItem::togglePlanes()
        {
            bool toggle;
            this->m_planeAxial->GetBoolProperty("visible", toggle);
            
            this->m_planeAxial->SetVisibility(!toggle);
            this->m_planeFrontal->SetVisibility(!toggle);
            this->m_planeSagittal->SetVisibility(!toggle);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto StdMultiItem::addPlanes() -> void
        {
            this->m_planeAxial      = this->m_viewerAxial->GetRenderer()->GetCurrentWorldPlaneGeometryNode();
            this->m_planeFrontal    = this->m_viewerFrontal->GetRenderer()->GetCurrentWorldPlaneGeometryNode();
            this->m_planeSagittal   = this->m_viewerSagittal->GetRenderer()->GetCurrentWorldPlaneGeometryNode();
            
            StdMultiItem::storage->Add(this->m_planeAxial);
            StdMultiItem::storage->Add(this->m_planeFrontal);
            StdMultiItem::storage->Add(this->m_planeSagittal);
        }
        
        auto StdMultiItem::moveCrossToPosition(const mitk::Point3D& newPosition) -> void
        {
            this->m_viewerAxial->GetSliceNavigationController()->SelectSliceByPoint(newPosition);
            this->m_viewerFrontal->GetSliceNavigationController()->SelectSliceByPoint(newPosition);
            this->m_viewerSagittal->GetSliceNavigationController()->SelectSliceByPoint(newPosition);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto StdMultiItem::getCrossPosition() -> mitk::Point3D const
        {
            const mitk::PlaneGeometry *plane1 = this->m_viewerAxial->GetSliceNavigationController()->GetCurrentPlaneGeometry();
            const mitk::PlaneGeometry *plane2 = this->m_viewerFrontal->GetSliceNavigationController()->GetCurrentPlaneGeometry();
            const mitk::PlaneGeometry *plane3 = this->m_viewerSagittal->GetSliceNavigationController()->GetCurrentPlaneGeometry();
            
            mitk::Line3D line;
            if ( (plane1 != NULL) && (plane2 != NULL)
                && (plane1->IntersectionLine( plane2, line )) )
            {
                mitk::Point3D point;
                if ( (plane3 != NULL)
                    && (plane3->IntersectionPoint( line, point )) )
                {
                    return point;
                }
            }

            mitk::Point3D p;
            return p;
        }
        
        
        auto StdMultiItem::getViewerAxial() -> RenderWindowItem*
        {
            return this->m_viewerAxial;
        }
        
        auto StdMultiItem::getViewerCoronal() -> RenderWindowItem*
        {
            return this->m_viewerFrontal;
        }
        
        auto StdMultiItem::getViewerSagittal() -> RenderWindowItem*
        {
            return this->m_viewerSagittal;
        }
        
        auto StdMultiItem::getViewerOriginal() -> RenderWindowItem*
        {
            return this->m_viewerOriginal;
        }
        
        void StdMultiItem::globalReinit()
        {
            mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(storage);
        }
    }
}
