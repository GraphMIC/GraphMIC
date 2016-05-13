#pragma once

#include "gmViewerExport.hpp"

#include "mitkDataNode.h"
#include "mitkPointSet.h"

#include <QAbstractListModel>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT PointListModel: public QAbstractListModel
        {
            Q_OBJECT
        protected:
            mitk::DataNode* m_pointSetNode;
            unsigned int    m_pointSetModifiedObserverTag;
            unsigned int    m_pointSetDeletedObserverTag;
            int             m_timeStep;
        public:
            PointListModel( mitk::DataNode* = NULL, int t = 0, QObject* parent = 0 );
            ~PointListModel();
            int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
            QVariant data(const QModelIndex& index, int role) const override;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
            auto setPointSetNode(mitk::DataNode* pointSetNode) -> void;
            auto getPointSet() -> const mitk::PointSet*;
            auto setTimeStep(int t) -> void;
            auto getTimeStep() -> const int;
            auto onPointSetChanged(const itk::EventObject &e) -> void;
            auto onPointSetDeleted(const itk::EventObject &e) -> void;
            auto getPointForModelIndex(const QModelIndex &index, mitk::PointSet::PointType &p, mitk::PointSet::PointIdentifier &id) const -> bool;
            auto getModelIndexForPointID(mitk::PointSet::PointIdentifier id, QModelIndex &index) const -> bool ;
        public slots:
            void moveSelectedPointUp();
            void moveSelectedPointDown();
            void removeSelectedPoint();
        signals:
            void signalUpdateSelection();
        protected:
            auto observeNewPointSet(mitk::DataNode* pointSetNode) -> void;
            auto checkForPointSetInNode(mitk::DataNode* node) const -> mitk::PointSet::Pointer;
        };
    }
}

