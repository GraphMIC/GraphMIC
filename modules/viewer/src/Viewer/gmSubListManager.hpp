#pragma once

#include "gmViewItemBase.hpp"
#include "gmViewerExport.hpp"

#include <mitkDataStorage.h>

#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        class DataStorageListModel;
        class GM_VIEWER_EXPORT SubListManager: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged);
            Q_PROPERTY(gm::ViewItem::DataStorageListModel* model READ getModel NOTIFY modelChanged);
            Q_PROPERTY(SubListType type READ getType WRITE setType NOTIFY typeChanged);
        public:
            enum SubListType
            {
                POINTSET,
                MEASUREMENT,
                MASKING,
                IMAGE
            };
            Q_ENUMS(SubListType)
        private:
            int                     m_index;
            DataStorageListModel*   m_dataModel;
            mitk::DataNode::Pointer m_ParentNode;
            SubListType             m_Type;
            bool                    m_Initialized;
        public:
            SubListManager();
            ~SubListManager();
            auto getIndex() -> int;
            auto setIndex(int index) -> void;
            auto setType(SubListType type) -> void;
            auto getType() -> SubListType;
            auto getModel() -> DataStorageListModel*;
        public slots:
            void toggleVisibility(bool checked);
            void reinitNode();
            void globalReinit();
            void init(int index);
            void addNode();
            void deleteNode();
            void changeNodeName(int index, QString name);
        signals:
            void indexChanged();
            void modelChanged();
            void typeChanged();
            void selectionChanged(mitk::DataNode::Pointer node);
        };
    }
}

