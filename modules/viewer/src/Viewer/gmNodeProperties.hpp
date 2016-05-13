#pragma once 

#include "gmViewerExport.hpp"
#include "gmSubListManager.hpp"

#include <mitkDataNode.h>
#include <mitkDataStorage.h>

#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        class NodeProperties : public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(QColor nodeColor READ getNodeColor WRITE setNodeColor NOTIFY nodeColorChanged);
            Q_PROPERTY(float nodeOpacity READ getNodeOpacity WRITE setNodeOpacity NOTIFY nodeOpacityChanged);
            Q_PROPERTY(gm::ViewItem::SubListManager::SubListType type READ getType WRITE setType NOTIFY typeChanged);
        private:
            mitk::DataNode::Pointer     m_selectedNode;
            mitk::DataStorage::Pointer  m_dataStorage;
            SubListManager::SubListType m_nodeType;
            QColor  m_nodeColor;
            float   m_NodeOpacity;
        public:
            static NodeProperties* instance;
        public:
            NodeProperties(mitk::DataStorage::Pointer storage);
            ~NodeProperties();
            auto setNodeColor(QColor color) -> void;
            auto getNodeColor() -> QColor;
            auto setNodeOpacity(float opacity) -> void;
            auto getNodeOpacity() -> float;
            auto setType(SubListManager::SubListType nodeType) -> void;
            auto getType() -> SubListManager::SubListType;
        public slots:
            void receive(mitk::DataNode::Pointer node);
            void chooseColor();
            void loadPointSet();
            void savePointSet();
            void convertMask();
            void deleteNode();
            void reinitNode();
        signals:
            void nodeColorChanged();
            void nodeOpacityChanged();
            void sync();
            void typeChanged();
        };
    }
}