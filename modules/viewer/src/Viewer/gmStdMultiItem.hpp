#pragma once

#include "gmViewItemBase.hpp"
#include "gmViewerExport.hpp"

#include <mitkDataStorage.h>
#include <mitkMouseModeSwitcher.h>

namespace gm
{
    namespace ViewItem
    {
        class RenderWindowItem;
        class GM_VIEWER_EXPORT StdMultiItem: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(int mouseMode READ getMouseMode WRITE setMouseMode)
        private:
            RenderWindowItem* m_viewerAxial;
            RenderWindowItem* m_viewerFrontal;
            RenderWindowItem* m_viewerSagittal;
            RenderWindowItem* m_viewerOriginal;
            mitk::DataNode::Pointer m_planeAxial;
            mitk::DataNode::Pointer m_planeFrontal;
            mitk::DataNode::Pointer m_planeSagittal;
            mitk::MouseModeSwitcher::Pointer m_mouseModeSwitcher;
            int m_mouseMode;
        public:
            static StdMultiItem* instance;
        public:
            StdMultiItem();
            ~StdMultiItem();
            auto registerViewerItem(RenderWindowItem* viewerItem) -> void;
            auto moveCrossToPosition(const mitk::Point3D& newPosition) -> void;
            auto addPlanes() -> void;
            auto getCrossPosition() -> mitk::Point3D const;
            auto setMouseMode(int mode) -> void;
            auto getMouseMode() -> int;
            auto getViewerAxial() -> RenderWindowItem*;
            auto getViewerSagittal() -> RenderWindowItem*;
            auto getViewerCoronal() -> RenderWindowItem*;
            auto getViewerOriginal() -> RenderWindowItem*;
        public slots:
            void init();
            void togglePlanes();
            void globalReinit();
        };
    }
}
