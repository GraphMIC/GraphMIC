#pragma once
#define US_MODULE_NAME MaskingItem

#include "gmViewItemBase.hpp"
#include "gmViewerExport.hpp"

#include "mitkToolManager.h"
#include "mitkDataNode.h"
#include "mitkImage.h"

#include <QQuickItem>
#include <QHash>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT MaskingItem: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(bool sliderEnabled READ isSliderEnabled WRITE setSliderEnabled NOTIFY sliderEnabledChanged);
            Q_PROPERTY(int sliderSize READ getSliderSize WRITE setSliderSize NOTIFY sliderSizeChanged);
        private:
            mitk::DataNode::Pointer     m_node;
            mitk::ToolManager::Pointer  m_toolManager;
            QHash<QString, mitk::Tool*> m_toolHash;
            int     m_registeredClients;
            int     m_sliderSize;
            bool    m_sliderEnabled;
        public:
            static MaskingItem* instance;
        public:
            MaskingItem();
            ~MaskingItem();
            static auto SetDataStorage(mitk::DataStorage::Pointer dataStorage) -> void;
            auto getToolIdByString(QString id) -> int;
            auto isSliderEnabled() -> bool;
            auto setSliderEnabled(bool status) -> void;
            auto setNodeProperties(mitk::DataNode::Pointer node) -> void;
            auto setSliderSize(int size) -> void;
            auto getSliderSize() -> int;
            auto updateInputs() -> void;
            auto maskImage(mitk::Image::Pointer referenceImage, mitk::Image::Pointer maskImage) -> mitk::Image::Pointer;
            auto addToDataStorage(mitk::Image::Pointer segmentation, const std::string& name, mitk::DataNode::Pointer parent) -> void;
            auto createNewMask(mitk::DataNode::Pointer node) -> void;
            auto initNode(mitk::DataNode::Pointer node) -> void;
            auto deactivateTool() -> void;
        public slots:
            void activateTool(QString id);
            void deactivateTool(QString id);
            void confirmMask();
            void receive(mitk::DataNode::Pointer node);
        signals:
            void sliderEnabledChanged();
            void sliderSizeChanged();
            void setStatus(bool status);
        };
    }
}