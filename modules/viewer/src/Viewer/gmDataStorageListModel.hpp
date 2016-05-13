#pragma once

#include "gmViewerExport.hpp"
#include "mitkDataStorage.h"
#include "mitkNodePredicateBase.h"

#include <QAbstractListModel>
#include <vector>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT DataStorageListModel: public QAbstractListModel
        {
            Q_OBJECT
        private:
            mitk::NodePredicateBase::Pointer m_nodePredicate;
            mitk::DataStorage*               m_dataStorage;
            std::vector<mitk::DataNode*>     m_dataNodes;
            std::vector<unsigned long>       m_dataNodesModifiedObserversTags;
            unsigned long                    m_dataStorageDeleteObserverTag;
            bool                             m_blockEvents;
        public:
            DataStorageListModel(mitk::DataStorage::Pointer dataStorage = nullptr, mitk::NodePredicateBase* pred = nullptr, QObject* parent = nullptr);
            ~DataStorageListModel();
            auto setDataStorage(mitk::DataStorage::Pointer dataStorage) -> void;
            auto getDataStorage() -> mitk::DataStorage::Pointer;
            auto setPredicate(mitk::NodePredicateBase* pred) -> void;
            auto getPredicate() -> mitk::NodePredicateBase*;
            auto getDataNodes() -> std::vector<mitk::DataNode*>;
            auto getNode(const QModelIndex &index) -> mitk::DataNode::Pointer;
            auto updateList() -> void;
            auto reset() -> void;
            virtual auto nodeAdded(const mitk::DataNode* node) -> void;
            virtual auto nodeRemoved(const mitk::DataNode* node) -> void;
            virtual auto nodeChanged(const mitk::DataNode* node) -> void;
            virtual auto onModified(const itk::Object* caller, const itk::EventObject &event) -> void;
            virtual auto onDelete(const itk::Object* caller, const itk::EventObject &event) -> void;
            Qt::ItemFlags flags(const QModelIndex& index) const override;
            QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
            int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        };
    }
}
