#include "gmPointListModel.hpp"
#include <itkCommand.h>
#include <mitkInteractionConst.h>
#include <mitkPointOperation.h>
#include <mitkRenderingManager.h>
#include <mitkPointSetDataInteractor.h>
#include <mitkInternalEvent.h>

namespace gm
{
    namespace ViewItem
    {
        PointListModel::PointListModel( mitk::DataNode* pointSetNode, int t, QObject* parent )
        :QAbstractListModel(parent),
        m_pointSetNode(NULL),
        m_pointSetModifiedObserverTag(0),
        m_pointSetDeletedObserverTag(0),
        m_timeStep(t)
        {
            observeNewPointSet(pointSetNode);
        }
        
        PointListModel::~PointListModel()
        {
            this->observeNewPointSet(NULL);
        }
        
        auto PointListModel::setPointSetNode(mitk::DataNode* pointSetNode) -> void
        {
            this->observeNewPointSet(pointSetNode);
            QAbstractListModel::beginResetModel();
            QAbstractListModel::endResetModel();
            emit signalUpdateSelection();
        }
        
        auto PointListModel::getPointSet() -> const mitk::PointSet*
        {
            return this->checkForPointSetInNode(m_pointSetNode);
        }
        
        auto PointListModel::setTimeStep(int t) -> void
        {
            m_timeStep = t;
            QAbstractListModel::beginResetModel();
            QAbstractListModel::endResetModel();
            emit signalUpdateSelection();
        }
        
        auto PointListModel::getTimeStep() -> const int
        {
            return m_timeStep;
        }
        
        auto PointListModel::observeNewPointSet(mitk::DataNode* pointSetNode) -> void
        {

            if (m_pointSetNode != NULL)
            {
                try
                {
                    mitk::PointSet::Pointer oldPointSet = dynamic_cast<mitk::PointSet*>(m_pointSetNode->GetData());
                    if (oldPointSet.IsNotNull())
                    {
                        oldPointSet->RemoveObserver(m_pointSetModifiedObserverTag);
                        oldPointSet->RemoveObserver(m_pointSetDeletedObserverTag);
                    }
                }
                catch(std::exception& e)
                {

                }
            }

            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(pointSetNode);
            
            m_pointSetNode = pointSetNode;
            
            if ( pointSet.IsNotNull())
            {

                itk::ReceptorMemberCommand<PointListModel>::Pointer modCommand = itk::ReceptorMemberCommand<PointListModel>::New();
                modCommand->SetCallbackFunction(this, &PointListModel::onPointSetChanged);
                m_pointSetModifiedObserverTag = pointSet->AddObserver( itk::ModifiedEvent(), modCommand );
                

                itk::ReceptorMemberCommand<PointListModel>::Pointer delCommand = itk::ReceptorMemberCommand<PointListModel>::New();
                delCommand->SetCallbackFunction(this, &PointListModel::onPointSetDeleted);
                m_pointSetDeletedObserverTag = pointSet->AddObserver( itk::DeleteEvent(), delCommand );
            }
            else
            {
                m_pointSetModifiedObserverTag = 0;
                m_pointSetDeletedObserverTag = 0;
            }
        }
        
        auto PointListModel::onPointSetChanged(const itk::EventObject &) -> void
        {
            QAbstractListModel::beginResetModel();
            QAbstractListModel::endResetModel();
            emit signalUpdateSelection();
        }
        
        auto PointListModel::onPointSetDeleted(const itk::EventObject &) -> void
        {
            mitk::PointSet::Pointer ps = checkForPointSetInNode(m_pointSetNode);
            if (ps)
            {
                ps->RemoveObserver(m_pointSetModifiedObserverTag);
                ps->RemoveObserver(m_pointSetDeletedObserverTag);
            }
            
            m_pointSetModifiedObserverTag = 0;
            m_pointSetDeletedObserverTag = 0;
            QAbstractListModel::beginResetModel();
            QAbstractListModel::endResetModel();
        }
        
        int PointListModel::rowCount(const QModelIndex&) const
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);

            if ( pointSet.IsNotNull() )
            {
                return pointSet->GetSize(m_timeStep);
            }
            else
            {
                return 0;
            }
        }
        
        QVariant PointListModel::data(const QModelIndex& index, int role) const
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            
            if ( pointSet.IsNull() )
            {
                return QVariant();
            }
            
            if ( !index.isValid() )
            {
                return QVariant();
            }
            
            if ( index.row() >= pointSet->GetSize(m_timeStep) )
            {
                return QVariant();
            }
            
            mitk::PointSet::PointsContainer::ElementIdentifier id;
            mitk::PointSet::PointType p;
            bool pointFound = this->getPointForModelIndex(index, p, id);
            if (!pointFound)
                return QVariant();
            
            switch (role)
            {
                case Qt::DisplayRole:
                {
                    QString s = QString("%0: (%1, %2, %3)")
                    .arg( id, 3)
                    .arg( p[0], 0, 'f', 3 )
                    .arg( p[1], 0, 'f', 3 )
                    .arg( p[2], 0, 'f', 3 );
                    return QVariant(s);
                }
                case Qt::DecorationRole:
                {
                    bool isSelected(pointSet->GetSelectInfo(id));
                    return QVariant(isSelected);
                }
                default:
                    return QVariant();
            }
        }
        
        QVariant PointListModel::headerData(int section, Qt::Orientation orientation, int role) const
        {
            if (role != Qt::DisplayRole)
            {
                return QVariant();
            }
            
            if (orientation == Qt::Horizontal)
            {
                return QString("Coordinates").arg(section);
            }
            else
            {
                return QString("Row %1").arg(section);
            }
        }
        
        auto PointListModel::getPointForModelIndex( const QModelIndex &index, mitk::PointSet::PointType& p, mitk::PointSet::PointIdentifier& id) const -> bool
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            if (pointSet.IsNull())
                return false;
            
            if ((index.row() < 0) || (index.row() >= (int)pointSet->GetPointSet(m_timeStep)->GetPoints()->Size()))
                return false;

            mitk::PointSet::PointsContainer::Iterator it = pointSet->GetPointSet(m_timeStep)->GetPoints()->Begin();
            for (int i = 0; i < index.row(); ++i)
            {
                ++it;
                
                if (it == pointSet->GetPointSet(m_timeStep)->GetPoints()->End())
                    return false;
                
            }
            
            if (it != pointSet->GetPointSet(m_timeStep)->GetPoints()->End())
            {
                p = it->Value();
                id = it->Index();
                return true;
            }
            
            return false;
        }
        
        auto PointListModel::getModelIndexForPointID(mitk::PointSet::PointIdentifier id, QModelIndex& index) const -> bool
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            if (pointSet.IsNull())
                return false;
            
            mitk::PointSet::PointsContainer::Pointer points = pointSet->GetPointSet(m_timeStep)->GetPoints();
            
            if (!points->IndexExists(id))
                return false;
            
            unsigned int idx = 0;
            for (auto it = points->Begin(); it != points->End(); ++it)
            {
                if (it->Index() == id)
                {
                    index = this->index(idx);
                    return true;
                }
                
                idx++;
            }
            
            return false; // nothing found
        }
        
        void PointListModel::moveSelectedPointUp()
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            if (pointSet.IsNull())
                return;
            
            mitk::PointSet::PointIdentifier selectedID;
            selectedID = pointSet->SearchSelectedPoint(m_timeStep);
            mitk::ScalarType tsInMS = pointSet->GetTimeGeometry()->TimeStepToTimePoint(m_timeStep);
            mitk::PointOperation* doOp = new mitk::PointOperation(mitk::OpMOVEPOINTUP,tsInMS, pointSet->GetPoint(selectedID, m_timeStep), selectedID, true);
            pointSet->ExecuteOperation(doOp);
            mitk::RenderingManager::GetInstance()->RequestUpdateAll();
        }
        
        void PointListModel::moveSelectedPointDown()
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            if (pointSet.IsNull())
                return;
            
            mitk::PointSet::PointIdentifier selectedID;
            selectedID = pointSet->SearchSelectedPoint(m_timeStep);
            mitk::ScalarType tsInMS = pointSet->GetTimeGeometry()->TimeStepToTimePoint(m_timeStep);
            mitk::PointOperation* doOp = new mitk::PointOperation(mitk::OpMOVEPOINTDOWN, tsInMS, pointSet->GetPoint(selectedID, m_timeStep), selectedID, true);
            pointSet->ExecuteOperation(doOp);
            mitk::RenderingManager::GetInstance()->RequestUpdateAll();
        }
        
        
        void PointListModel::removeSelectedPoint()
        {
            mitk::PointSet::Pointer pointSet = this->checkForPointSetInNode(m_pointSetNode);
            if (pointSet.IsNull())
                return;
            
            mitk::PointSet::PointIdentifier selectedID;
            selectedID = pointSet->SearchSelectedPoint(m_timeStep);
            mitk::ScalarType tsInMS = pointSet->GetTimeGeometry()->TimeStepToTimePoint(m_timeStep);
            mitk::PointOperation* doOp = new mitk::PointOperation(mitk::OpREMOVE, tsInMS, pointSet->GetPoint(selectedID, m_timeStep), selectedID, true);
            pointSet->ExecuteOperation(doOp);
            mitk::RenderingManager::GetInstance()->RequestUpdateAll();
        }

        auto PointListModel::checkForPointSetInNode(mitk::DataNode* node) const -> mitk::PointSet::Pointer
        {
            if (node != NULL)
            {
                mitk::PointSet::Pointer pointSet = dynamic_cast<mitk::PointSet*>(node->GetData());
                if (pointSet.IsNotNull())
                    return pointSet;
            }
            return NULL;
        }
    }
}

