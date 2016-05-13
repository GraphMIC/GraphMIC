#include "gmSubListManager.hpp"

#include <mitkImage.h>
#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateOr.h>
#include <mitkNodePredicateProperty.h>
#include <mitkNodePredicateSource.h>

#include <QQmlContext>
#include <QModelIndex>

#include <gmTransferFunctionItem.hpp>
#include <gmMeasurementItem.hpp>
#include <gmDataStorageListModel.hpp>
#include <gmPointListItem.hpp>
#include <gmDatamanager.hpp>
#include <gmMaskingItem.hpp>

namespace gm
{
    namespace ViewItem
    {
        SubListManager::SubListManager(): m_dataModel(new DataStorageListModel()), m_Initialized(false)
        {
            if(!DataManager::instance)
                throw("DataManager not set");
            connect(this, &SubListManager::selectionChanged, DataManager::instance, &DataManager::setSelectedNode);

            SetDataStorage(DataManager::instance->getDataStorage());
        }
        
        SubListManager::~SubListManager()
        {
            this->m_dataModel->setDataStorage(nullptr);
            delete this->m_dataModel;
        }

        auto SubListManager::setType(SubListType type) -> void
        {
            this->m_Type = type;
            emit this->typeChanged();
        }
        
        auto SubListManager::getType() -> SubListType
        {
            return this->m_Type;
        }
        
        void SubListManager::changeNodeName(int index, QString name)
        {
            QModelIndex modelIndex = this->m_dataModel->index(index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
            node->SetName(name.toStdString());
        }
        
        void SubListManager::init(int index)
        {
            if(!m_Initialized)
            {
                this->m_dataModel->setDataStorage(storage);
                
                QModelIndex modelIndex = DataManager::instance->getDataModel()->index(index);
                this->m_ParentNode = DataManager::instance->getDataModel()->getNode(modelIndex);
                
                if(!this->m_ParentNode)
                    return;
                
                std::string typeString;
                switch (this->m_Type)
                {
                    case SubListType::POINTSET:
                        typeString = "pointSet";
                        break;
                    case SubListType::MEASUREMENT:
                        typeString = "measurement";
                        break;
                    case SubListType::MASKING:
                        typeString = "masking";
                        break;
                    default: return;
                }
                mitk::BoolProperty::Pointer boolProp = mitk::BoolProperty::New(true);
                mitk::NodePredicateProperty::Pointer typeFilter = mitk::NodePredicateProperty::New(typeString.c_str(), boolProp);
                mitk::NodePredicateSource::Pointer sourcefilter = mitk::NodePredicateSource::New(this->m_ParentNode, true, storage);
                mitk::NodePredicateAnd::Pointer andFilter = mitk::NodePredicateAnd::New(typeFilter, sourcefilter);

                this->m_dataModel->setPredicate(andFilter);
                this->m_Initialized = true;
            }
        }
        
        auto SubListManager::getModel() -> DataStorageListModel*
        {
            return this->m_dataModel;
        }
        
        void SubListManager::toggleVisibility(bool checked)
        {
            QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
            node->SetVisibility(checked);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto SubListManager::setIndex(int index) -> void
        {
            this->m_index = index;
            
            if(index >= 0)
            {
                QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
                mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);
                emit this->selectionChanged(node);
            }
            this->m_dataModel->updateList();
            emit this->indexChanged();
        }
        
        auto SubListManager::getIndex() -> int
        {
            return this->m_index;
        }
        
        void SubListManager::reinitNode()
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
        
        void SubListManager::addNode()
        {
            mitk::DataNode::Pointer node = mitk::DataNode::New();
            switch (this->m_Type)
            {
                case SubListType::POINTSET:
                    PointListItem::instance->setNodeProperties(node);
                    storage->Add(node, this->m_ParentNode);
                    break;
                case SubListType::MEASUREMENT:
                    MeasurementItem::instance->setNodeProperties(node);
                    storage->Add(node, this->m_ParentNode);
                    break;
                case SubListType::MASKING:
                    MaskingItem::instance->setNodeProperties(node);
                    storage->Add(node, this->m_ParentNode);
                    break;
                default: return;
            }
        }
        
        void SubListManager::globalReinit()
        {
            mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(SubListManager::storage);
        }
        
        void SubListManager::deleteNode()
        {
            QModelIndex modelIndex = this->m_dataModel->index(this->m_index);
            mitk::DataNode::Pointer node = this->m_dataModel->getNode(modelIndex);

            emit this->selectionChanged(nullptr);
            storage->Remove(node);
            this->globalReinit();
        }
    }
}
