#pragma once
#include "gmViewerExport.hpp"
#include "gmViewItemBase.hpp"
#include <mitkDataStorage.h>

namespace gm
{
    namespace ViewItem
    {
        class DataStorageListModel;
        class GM_VIEWER_EXPORT DataManager: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged);
            Q_PROPERTY(gm::ViewItem::DataStorageListModel* model READ getModel CONSTANT);
        private:
            int                         m_index;
            DataStorageListModel*       m_dataModel;
            mitk::DataNode::Pointer     m_selectedNode;
            mitk::DataStorage::Pointer  m_dataStorage;
        public:
            static DataManager* instance;
        public:
            DataManager(mitk::DataStorage::Pointer dataStorage);
            DataManager() = delete;
            ~DataManager();
            auto getIndex() -> int;
            auto setIndex(int index) -> void;
            auto getDataModel() -> DataStorageListModel*;
            auto getModel() -> DataStorageListModel*;
            auto getDataStorage() -> mitk::DataStorage::Pointer;
            auto getSelectedNode() -> mitk::DataNode::Pointer;
        public slots:
            void toggleVisibility(bool checked);
            void reinitNode();
            void globalReinit();
            void deleteNode(mitk::DataNode::Pointer node);
            void setSelectedNode(mitk::DataNode::Pointer node);
            void changeNodeName(int index, QString name);
        signals:
            void indexChanged();
            void notifySelection(mitk::DataNode::Pointer node);
        };
    }
}

