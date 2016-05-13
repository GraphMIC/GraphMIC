#include "gmNodeProperties.hpp"
#include "gmDatamanager.hpp"
#include "gmMaskingItem.hpp"
#include "gmPointListItem.hpp"
#include <mitkLabelSetImage.h>
#include <mitkLabel.h>
#include <QColorDialog>
namespace gm
{
    namespace ViewItem
    {
        NodeProperties* NodeProperties::instance = nullptr;
        
        NodeProperties::NodeProperties(mitk::DataStorage::Pointer storage):
        m_dataStorage(storage),
        m_NodeOpacity(1.0)
        {
            if(instance)
            {
                throw("Instance already existing");
            }
            instance = this;
            setEnabled(false);
            connect(DataManager::instance, &DataManager::notifySelection, this, &NodeProperties::receive);
        }
        
        NodeProperties::~NodeProperties()
        {
            
        }
        
        void NodeProperties::reinitNode()
        {
            mitk::BaseData::Pointer basedata = this->m_selectedNode->GetData();
            if ( basedata.IsNotNull() &&
                basedata->GetTimeGeometry()->IsValid() )
            {
                mitk::RenderingManager::GetInstance()->InitializeViews(basedata->GetTimeGeometry(), mitk::RenderingManager::REQUEST_UPDATE_ALL, true );
            }
        }
        
        void NodeProperties::deleteNode()
        {
            if(m_selectedNode)
            {
                DataManager::instance->deleteNode(this->m_selectedNode);
                //this->m_dataStorage->Remove(this->m_selectedNode);
            }
        }
        
        void NodeProperties::receive(mitk::DataNode::Pointer node)
        {
            if(!node)
            {
                setEnabled(false);
                return;
            }

            setEnabled(true);
            
            if(this->m_selectedNode ==  node)
                return;
            
            float rgb[3]    = {1.0f, 0.0f, 0.0f};
            float opacity   = 1.0;
            
            this->m_selectedNode = node;
            this->m_selectedNode->GetOpacity(opacity, nullptr);
            this->m_selectedNode->GetColor(rgb);
            
            this->m_NodeOpacity = opacity*100;
            this->m_nodeColor = QColor(rgb[0]*255, rgb[1]*255, rgb[2]*255);
            
            bool isPointSet     = false;
            bool isMasking      = false;
            bool isImage        = false;
            bool isMeasurement  = false;
            
            this->m_selectedNode->GetBoolProperty("pointSet", isPointSet);
            this->m_selectedNode->GetBoolProperty("masking", isMasking);
            this->m_selectedNode->GetBoolProperty("image", isImage);
            this->m_selectedNode->GetBoolProperty("measurement", isMeasurement);
            
            if(isPointSet)
                this->setType(SubListManager::SubListType::POINTSET);
            else if(isMasking)
                this->setType(SubListManager::SubListType::MASKING);
            else if(isImage)
                this->setType(SubListManager::SubListType::IMAGE);
            else if(isMeasurement)
                this->setType(SubListManager::SubListType::MEASUREMENT);
            
            emit this->sync();
        }
        
        auto NodeProperties::setNodeOpacity(float opacity) -> void
        {
            this->m_NodeOpacity = opacity;
            this->m_selectedNode->SetOpacity(opacity/100);
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            emit this->nodeOpacityChanged();
        }
        
        auto NodeProperties::getNodeOpacity() -> float
        {
            return this->m_NodeOpacity;
        }
        
        auto NodeProperties::setNodeColor(QColor color) -> void
        {
            this->m_nodeColor = color;
            
            mitk::LabelSetImage* labelSet = dynamic_cast<mitk::LabelSetImage*>(this->m_selectedNode->GetData());
            if(labelSet)
            {
                mitk::Color c;
                c.Set(color.redF(), color.greenF(), color.blueF());
                labelSet->GetActiveLabel()->SetColor(c);
            }
            else
            {
                if(this->m_selectedNode->GetData())
                {
                    this->m_selectedNode->SetColor(color.redF(), color.greenF(), color.blueF());
                }
            }
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            emit this->nodeColorChanged();
        }
        
        auto NodeProperties::getNodeColor() -> QColor
        {
            return this->m_nodeColor;
        }
        
        auto NodeProperties::setType(SubListManager::SubListType nodeType) -> void
        {
            this->m_nodeType = nodeType;
            emit this->typeChanged();
        }
        
        auto NodeProperties::getType() -> SubListManager::SubListType
        {
            return this->m_nodeType;
        }
        
        void NodeProperties::convertMask()
        {
            MaskingItem::instance->confirmMask();
        }
        
        void NodeProperties::loadPointSet()
        {
            PointListItem::instance->loadPoints();
        }
        
        void NodeProperties::savePointSet()
        {
            PointListItem::instance->savePoints();
        }
        
        void NodeProperties::chooseColor()
        {
            QColor color = QColorDialog::getColor();
            this->setNodeColor(color);
        }
    }
}