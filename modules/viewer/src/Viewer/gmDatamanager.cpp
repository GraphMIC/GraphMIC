#include "gmDatamanager.hpp"

#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateOr.h>
#include <mitkNodePredicateProperty.h>
#include <gmTransferFunctionItem.hpp>
#include <gmDataStorageListModel.hpp>

namespace gm
{
    namespace ViewItem
    {
        DataManager* DataManager::instance = nullptr;

        DataManager::DataManager(mitk::DataStorage::Pointer dataStorage):
        m_dataStorage(dataStorage),
        m_selectedNode(nullptr)
        {
            if(instance)
            {
                throw("Instance already existing");
            }

            instance = this;
            
            mitk::NodePredicateProperty::Pointer pred   = mitk::NodePredicateProperty::New("helper object", mitk::BoolProperty::New(false));
            mitk::NodePredicateProperty::Pointer pred1  = mitk::NodePredicateProperty::New("image", mitk::BoolProperty::New(true));
            mitk::NodePredicateOr::Pointer filter       = mitk::NodePredicateOr::New(pred, pred1);
            
            this->m_dataModel = new DataStorageListModel(dataStorage, filter);
        }
        
        DataManager::~DataManager()
        {
            delete this->m_dataModel;
        }
        
        void DataManager::toggleVisibility(bool checked)
        {
            QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
            node->SetVisibility(checked);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto DataManager::getSelectedNode() -> mitk::DataNode::Pointer
        {
            return this->m_selectedNode;
        }
        
        auto DataManager::setSelectedNode(mitk::DataNode::Pointer node) -> void
        {
            if(this->m_selectedNode)
            {
                this->m_selectedNode->SetSelected(false);
                this->m_selectedNode->Modified();
            }
            
            if(node)
            {
                this->m_selectedNode = node;
                this->m_selectedNode->SetSelected(true);
                this->m_selectedNode->Modified();
            }
            else
            {
                this->m_selectedNode = nullptr;
            }
            
            emit this->notifySelection(node);
        }
        
        auto DataManager::setIndex(int index) -> void
        {
            this->m_index = index;
            
            if(index >= 0)
            {
                QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
                mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
                
                this->setSelectedNode(node);
            }
            
            emit this->indexChanged();
        }
        
        auto DataManager::getDataModel() -> DataStorageListModel*
        {
            return this->m_dataModel;
        }
        
        auto DataManager::getIndex() -> int
        {
            return this->m_index;
        }
        
        void DataManager::reinitNode()
        {
            QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
            
            mitk::BaseData::Pointer basedata = node->GetData();
            if ( basedata.IsNotNull() &&
                basedata->GetTimeGeometry()->IsValid() )
            {
                mitk::RenderingManager::GetInstance()->InitializeViews(basedata->GetTimeGeometry(), mitk::RenderingManager::REQUEST_UPDATE_ALL, true );
            }
        }
        
        auto DataManager::getModel() -> DataStorageListModel*
        {
            return this->m_dataModel;
        }
        
        void DataManager::globalReinit()
        {
            mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(this->m_dataStorage);
        }
        
        void DataManager::changeNodeName(int index, QString name)
        {
            QModelIndex modelIndex = this->m_dataModel->index(index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
            node->SetName(name.toStdString());
        }
        
        void DataManager::deleteNode(mitk::DataNode::Pointer node)
        {
         //   QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
         //   mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);

            this->setSelectedNode(nullptr);
            this->m_dataStorage->Remove(node);
            this->globalReinit();
        }

        auto DataManager::getDataStorage() -> mitk::DataStorage::Pointer
        {
            return this->m_dataStorage;
        }
    }
}
