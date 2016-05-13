#include "gmDataStorageListModel.hpp"
#include "itkCommand.h"

namespace gm
{
    namespace ViewItem
    {
        DataStorageListModel::DataStorageListModel(mitk::DataStorage::Pointer dataStorage, mitk::NodePredicateBase* pred, QObject* parent)
        : QAbstractListModel(parent), m_nodePredicate(nullptr), m_dataStorage(nullptr), m_blockEvents(false)
        {
            this->setPredicate(pred);
            this->setDataStorage(dataStorage);
        }
        
        DataStorageListModel::~DataStorageListModel()
        {
            this->reset();
            this->setDataStorage(nullptr);
            this->m_dataNodes.clear();
        }
        
        auto DataStorageListModel::setDataStorage(mitk::DataStorage::Pointer dataStorage) -> void
        {
            if( m_dataStorage != dataStorage)
            {
                if(m_dataStorage != nullptr)
                {
                    this->m_dataStorage->AddNodeEvent.RemoveListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeAdded) );
                    this->m_dataStorage->ChangedNodeEvent.RemoveListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeChanged) );
                    this->m_dataStorage->RemoveNodeEvent.RemoveListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeRemoved) );
                    
                    m_dataStorage->RemoveObserver(m_dataStorageDeleteObserverTag);
                    m_dataStorageDeleteObserverTag = 0;
                }
                
                m_dataStorage = dataStorage;
                
                if(m_dataStorage != nullptr)
                {
                    
                    this->m_dataStorage->AddNodeEvent.AddListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeAdded) );
                    this->m_dataStorage->ChangedNodeEvent.AddListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeChanged) );
                    this->m_dataStorage->RemoveNodeEvent.AddListener(mitk::MessageDelegate1<DataStorageListModel, const mitk::DataNode*>(this, &DataStorageListModel::nodeRemoved) );
                    
                    itk::MemberCommand<DataStorageListModel>::Pointer deleteCommand =
                    itk::MemberCommand<DataStorageListModel>::New();
                    deleteCommand->SetCallbackFunction(this, &DataStorageListModel::onDelete);
                    m_dataStorageDeleteObserverTag = m_dataStorage->AddObserver(itk::DeleteEvent(), deleteCommand);
                    
                }
                
                reset();
            }
        }
        
        Qt::ItemFlags DataStorageListModel::flags(const QModelIndex&) const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        
        QVariant DataStorageListModel::data(const QModelIndex& index, int role) const
        {
            if(index.isValid())
            {
                const mitk::DataNode* node = m_dataNodes.at(index.row());
                
                switch (role)
                {
                    case Qt::DisplayRole:
                    {
                        std::string name = node->GetName();
                        return QVariant(QString::fromStdString(name));
                    }
                    case Qt::DecorationRole:
                    {
                        bool isSelected = const_cast<mitk::DataNode*>(node)->IsSelected();
                        return QVariant(isSelected);
                    }
                    default:
                        return QVariant();
                }
            }
            
            return QVariant();
        }
        
        auto DataStorageListModel::updateList() -> void
        {
            dataChanged(index(0, 0), index(rowCount() - 1, 0));
        }
        
        QVariant DataStorageListModel::headerData(int  /*section*/, Qt::Orientation  /*orientation*/, int  /*role*/) const
        {
            return QVariant("Nodes");
        }
        
        int DataStorageListModel::rowCount(const QModelIndex&  /*parent*/) const
        {
            return m_dataNodes.size();
        }
        
        auto DataStorageListModel::getDataNodes() -> std::vector<mitk::DataNode*>
        {
            return m_dataNodes;
        }
        
        auto DataStorageListModel::getDataStorage() -> mitk::DataStorage::Pointer
        {
            return m_dataStorage;
        }

        auto DataStorageListModel::setPredicate(mitk::NodePredicateBase* pred) -> void
        {
            m_nodePredicate = pred;
            reset();
            QAbstractListModel::beginResetModel();
            QAbstractListModel::endResetModel();
        }
        
        auto DataStorageListModel::getPredicate() -> mitk::NodePredicateBase*
        {
            return m_nodePredicate;
        }
        
        auto DataStorageListModel::reset() -> void
        {
            if(m_dataStorage != nullptr)
            {
                mitk::DataStorage::SetOfObjects::ConstPointer setOfObjects;
                
                if (m_nodePredicate)
                {
                    setOfObjects = m_dataStorage->GetSubset(m_nodePredicate);
                }
                else
                {
                    setOfObjects = m_dataStorage->GetAll();
                }
                
                unsigned int i = 0;
                for(auto it= m_dataNodes.begin(); it!= m_dataNodes.end(); ++it, ++i)
                {
                    (*it)->RemoveObserver(m_dataNodesModifiedObserversTags[i]);
                }
                
                m_dataNodesModifiedObserversTags.clear();
                m_dataNodes.clear();
                itk::MemberCommand<DataStorageListModel>::Pointer modifiedCommand;
                for (auto nodeIt = setOfObjects->Begin(); nodeIt != setOfObjects->End(); ++nodeIt, ++i)
                {
                    modifiedCommand = itk::MemberCommand<DataStorageListModel>::New();
                    modifiedCommand->SetCallbackFunction(this, &DataStorageListModel::onModified);
                    m_dataNodesModifiedObserversTags.push_back( m_dataStorage->AddObserver(itk::ModifiedEvent(), modifiedCommand) );
                    m_dataNodes.push_back( nodeIt.Value().GetPointer());
                    
                }
            }
        }
        
        auto DataStorageListModel::nodeChanged(const mitk::DataNode* /*node*/) -> void
        {
            updateList();
        }
        
        void DataStorageListModel::nodeAdded(const mitk::DataNode* node)
        {
            if(!m_blockEvents)
            {
                m_blockEvents = true;

                bool addNode = true;
                if(m_nodePredicate && !m_nodePredicate->CheckNode(node))
                    addNode = false;
                
                if(addNode)
                {
                    beginInsertRows(QModelIndex(), m_dataNodes.size(), m_dataNodes.size());
                    m_dataNodes.push_back(const_cast<mitk::DataNode*>(node));
                    endInsertRows();
                }
                m_blockEvents = false;
            }
        }
        
        auto DataStorageListModel::nodeRemoved(const mitk::DataNode* node) -> void
        {
            mitk::DataStorage::SetOfObjects::ConstPointer derivatives = m_dataStorage->GetDerivations(node);
            for (auto objectIter = derivatives->begin(); objectIter != derivatives->end();++objectIter)
            {
                mitk::DataNode* node = (*objectIter).GetPointer();
                this->m_dataStorage->Remove(node);
            }
            
            if(!m_blockEvents)
            {
                m_blockEvents = true;
                
                int row = -1;
                for (auto nodeIt = m_dataNodes.begin(); nodeIt != m_dataNodes.end(); nodeIt++)
                {
                    row++;
                    if( (*nodeIt) == node )
                    {
                        beginRemoveRows(QModelIndex(), row, row);
                        m_dataNodes.erase(std::find(m_dataNodes.begin(), m_dataNodes.end(), (*nodeIt)));
                        endRemoveRows();
                        
                        break;
                    }
                }
                
                m_blockEvents = false;
            }
        }
        
        auto DataStorageListModel::onModified(const itk::Object* caller, const itk::EventObject & /*event*/ ) -> void
        {
            if(m_blockEvents) return;
            
            const mitk::DataNode* modifiedNode = dynamic_cast<const mitk::DataNode*>(caller);
            if(modifiedNode)
            {
                int row = std::distance(std::find(m_dataNodes.begin(), m_dataNodes.end(), modifiedNode), m_dataNodes.end());
                QModelIndex indexOfChangedProperty = index(row, 1);
                
                emit dataChanged(indexOfChangedProperty, indexOfChangedProperty);
            }
        }
        
        auto DataStorageListModel::onDelete(const itk::Object* caller, const itk::EventObject & /*event*/ ) -> void
        {
            if(m_blockEvents) return;
            
            const mitk::DataStorage* dataStorage = dynamic_cast<const mitk::DataStorage*>(caller);
            if(dataStorage)
            {
                this->setDataStorage(nullptr);
            }
        }
        
        auto DataStorageListModel::getNode( const QModelIndex &index ) -> mitk::DataNode::Pointer
        {
            mitk::DataNode::Pointer node;
            
            if(index.isValid())
            {
                node = m_dataNodes.at(index.row());
            }
            
            return node;
        }
    }
}
