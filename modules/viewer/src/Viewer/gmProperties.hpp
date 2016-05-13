#pragma once

#include "gmViewerExport.hpp"

#include <mitkDataNode.h>
#include <mitkWeakPointer.h>

#include <QObject>
#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        enum RenderMode
        {
            RM_CPU_COMPOSITE_RAYCAST = 0,
            RM_CPU_MIP_RAYCAST       = 1,
            RM_GPU_COMPOSITE_SLICING = 2,
            RM_GPU_COMPOSITE_RAYCAST = 3,
            RM_GPU_MIP_RAYCAST       = 4
        };
        
        class GM_VIEWER_EXPORT VolumeProperties: public QQuickItem
        {
            Q_OBJECT
            Q_ENUMS(RenderMode)
            Q_PROPERTY(bool rendering READ getRendering WRITE setRendering NOTIFY renderingChanged);
            Q_PROPERTY(bool lod READ getLod WRITE setLod NOTIFY lodChanged);
            Q_PROPERTY(int mode READ getMode WRITE setMode NOTIFY modeChanged);
        private:
            bool    m_rendering;
            bool    m_lod;
            int     m_mode;
            mitk::WeakPointer<mitk::DataNode> m_node;
        public:
            static VolumeProperties* instance;
        public:
            VolumeProperties();
            ~VolumeProperties();
            auto setRendering(bool state) -> void;
            auto setLod(bool state) -> void;
            auto setMode(int mode) -> void;
            auto getRendering() -> bool;
            auto getLod() -> bool;
            auto getMode() -> int;
        signals:
            void renderingChanged();
            void lodChanged();
            void modeChanged();
            void sync();
            void setStatus(bool status);
        protected slots:
            void receive(mitk::DataNode::Pointer node);
        };
    }
}