#pragma once

#include "gmPointListModel.hpp"
#include "gmViewItemBase.hpp"
#include "gmViewerExport.hpp"

#include <mitkDataNode.h>
#include <mitkPointSet.h>
#include <mitkDataInteractor.h>
#include <mitkSliceNavigationController.h>

#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        class PointListModel;
        
        class PointListItem: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(bool pointEdit READ isPointEdit WRITE setPointEdit NOTIFY pointEditChanged);
            Q_PROPERTY(int selectedIndex READ getSelectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged);
            Q_PROPERTY(QObject* selectedItem READ getSelectedItem WRITE setSelectedItem NOTIFY selectedItemChanged);
            Q_PROPERTY(gm::ViewItem::PointListModel* pointListModel READ getPointListModel CONSTANT);
        protected:
            mitk::DataNode::Pointer         m_PointSetNode;
            mitk::DataInteractor::Pointer   m_DataInteractor;
            PointListModel*                 m_PointListModel;
            QObject*                        m_SelectedItem;
            int     m_TimeStep;
            int     m_SelectedIndex;
            bool    m_PointEdit;
            bool    m_SelfCall;
            long    m_NodeObserverTag;
        public:
            static PointListItem* instance;
        public:
            PointListItem(QObject *parent = 0, int orientation = 0);
            ~PointListItem();
            auto getSelectedItem() -> QObject*;
            auto setSelectedItem(QObject* item) -> void;
            auto disableInteractor() -> void;
            auto updateSelection(mitk::DataNode::Pointer node) -> void;
            auto setSelectedIndex(int index) ->void;
            auto getSelectedIndex() -> int;
            auto setPointEdit(bool status) -> void;
            auto isPointEdit() -> bool;
            auto setPointSet(mitk::PointSet* newPs) -> void;
            auto getPointSet() -> mitk::PointSet*;
            auto setPointSetNode(mitk::DataNode* newNode) -> void;
            auto getPointSetNode() -> mitk::DataNode*;
            auto onNodeDeleted(const itk::EventObject &e) -> void;
            auto getPointListModel() -> PointListModel*;
            auto resetList() -> void;
            auto setNodeProperties(mitk::DataNode::Pointer node) -> void;
            auto savePoints() -> void;
            auto loadPoints() -> void;
            auto observeNewNode(mitk::DataNode* node) -> void;
        signals:
            void pointSelectionChanged();
            void pointListChanged();
            void pointEditChanged();
            void selectedIndexChanged();
            void setStatus(bool status);
            void selectedItemChanged();
        protected slots:
            void removeSelectedPoint();
            void moveSelectedPointDown();
            void moveSelectedPointUp();
            void addPoint(bool enabled);
            void onPointSetSelectionChanged();
            void receive(mitk::DataNode::Pointer node);
            void onListViewSelectionChanged(int index);
        };
    }
}


