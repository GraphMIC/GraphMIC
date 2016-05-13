#include "gmPointListItem.hpp"
#include <QQmlContext>
#include <QFileDialog>
#include <mitkIOUtil.h>
#include <mitkPointSetDataInteractor.h>
#include "gmStdMultiItem.hpp"
#include "gmDatamanager.hpp"
#include "gmPropertyController.hpp"

namespace gm
{
    namespace ViewItem
    {
        PointListItem* PointListItem::instance = nullptr;

        PointListItem::PointListItem(QObject* parent, int orientation) :
        m_PointSetNode(NULL),
        m_DataInteractor(NULL),
        m_PointListModel(new PointListModel()),
        m_SelectedItem(NULL),
        m_TimeStep(0),
        m_PointEdit(false),
        m_SelfCall(false),
        m_NodeObserverTag(0)
        {
            if(instance)
            {
                throw ("Instance already existing");
            }
            instance = this;
            observeNewNode(NULL);
            setEnabled(false);
            
            connect(m_PointListModel, &PointListModel::signalUpdateSelection, this, &PointListItem::onPointSetSelectionChanged);
            connect(DataManager::instance, &DataManager::notifySelection, this, &PointListItem::receive);
            connect(this, &PointListItem::setStatus, PropertyController::instance, &PropertyController::setPointSet);
        }
        
        PointListItem::~PointListItem()
        {
            m_DataInteractor = NULL;
            
            if(m_PointSetNode && m_NodeObserverTag)
            {
                m_PointSetNode->RemoveObserver(m_NodeObserverTag);
                m_NodeObserverTag = 0;
            }
            
            delete m_PointListModel;
        }
        
        auto PointListItem::getPointListModel() -> PointListModel*
        {
            return this->m_PointListModel;
        }
        
        auto PointListItem::getSelectedItem() -> QObject*
        {
            return this->m_SelectedItem;
        }
        
        auto PointListItem::setSelectedItem(QObject* item) -> void
        {
            if(this->m_SelectedItem == item)
            {
                return;
            }
            
            this->m_SelectedItem = item;
            emit this->selectedItemChanged();
        }

        void PointListItem::receive(mitk::DataNode::Pointer node)
        {
            if(node && dynamic_cast<mitk::PointSet*>(node->GetData()))
            {
                this->updateSelection(node);
                setEnabled(true);
                emit this->setStatus(true);
            }
            else
            {
                this->resetList();
                setEnabled(false);
                emit this->setStatus(false);
            }
        }
        
        void PointListItem::onListViewSelectionChanged(int selectedIndex)
        {
            
            if(m_SelfCall)
            {
                return;
            }

            mitk::PointSet* pointSet = const_cast<mitk::PointSet*>( this->m_PointListModel->getPointSet());

            if(pointSet == NULL)
            {
                return;
            }
            
            for(auto it = pointSet->GetPointSet(m_PointListModel->getTimeStep())->GetPoints()->Begin();
                it != pointSet->GetPointSet(m_PointListModel->getTimeStep())->GetPoints()->End(); ++it)
            {
                pointSet->SetSelectInfo(it->Index(), false, m_PointListModel->getTimeStep());
            }
            
            m_SelfCall = true;
            
            for(auto it = pointSet->GetPointSet(m_PointListModel->getTimeStep())->GetPoints()->Begin();
                it != pointSet->GetPointSet(m_PointListModel->getTimeStep())->GetPoints()->End(); ++it)
            {
                QModelIndex index;
                if(m_PointListModel->getModelIndexForPointID(it->Index(), index))
                {
                    if(index.row() == selectedIndex)
                    {
                        pointSet->SetSelectInfo(it->Index(), true, m_PointListModel->getTimeStep());
                        StdMultiItem::instance->moveCrossToPosition(pointSet->GetPoint(it->Index()));
                    }
                }
            }
            
            m_SelfCall = false;
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto PointListItem::setPointSet(mitk::PointSet* newPs) -> void
        {
            if(newPs == NULL)
            {
                return;
            }
            
            this->m_PointSetNode->SetData(newPs);
            this->m_PointListModel->setPointSetNode(m_PointSetNode);
            observeNewNode(m_PointSetNode);
        }
        
        auto PointListItem::setPointSetNode(mitk::DataNode* newNode) -> void
        {
            if(m_DataInteractor.IsNotNull())
            {
                m_DataInteractor->SetDataNode(newNode);
            }
            
            observeNewNode(newNode);
            this->m_PointListModel->setPointSetNode(newNode);
        }
        
        auto PointListItem::savePoints() -> void
        {
            if((dynamic_cast<mitk::PointSet*>(m_PointSetNode->GetData())) == NULL)
            {
                return;
            }
            if((dynamic_cast<mitk::PointSet*>(m_PointSetNode->GetData()))->GetSize() == 0)
            {
                return;
            }
            
            std::string nodeName = m_PointSetNode->GetName();
            nodeName = "/" + nodeName + ".mps";
            QString fileNameProposal = QString();
            fileNameProposal.append(nodeName.c_str());
            
            QString aFilename = QFileDialog::getSaveFileName(NULL, "Save point set", QDir::currentPath() + fileNameProposal, "Pointset (*.mps)");
            if(aFilename.isEmpty())
            {
                return;
            }
            
            try
            {
                mitk::IOUtil::Save(m_PointSetNode->GetData(), aFilename.toStdString());
            }
            catch(...)
            {

            }
        }
        
        auto PointListItem::loadPoints() -> void
        {
            QString filename = QFileDialog::getOpenFileName(NULL, "Open Pointset", "", "Point Sets (*.mps)");
            if(filename.isEmpty())
            {
                return;
            }
            
            try
            {
                mitk::PointSet::Pointer pointSet = mitk::IOUtil::LoadPointSet(filename.toStdString());
                if(pointSet.IsNull())
                {
                    return;
                }
                this->setPointSet(pointSet);
            }
            catch(...)
            {
            }
            emit pointListChanged();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto PointListItem::getPointSet() -> mitk::PointSet*
        {
            return dynamic_cast<mitk::PointSet*>(m_PointSetNode->GetData());
        }
        
        auto PointListItem::getPointSetNode() -> mitk::DataNode*
        {
            return m_PointSetNode;
        }
        
        void PointListItem::onPointSetSelectionChanged()
        {
            const mitk::PointSet* pointSet = m_PointListModel->getPointSet();
            if(pointSet == NULL)
            {
                return;
            }
            
            m_SelfCall = true;
            int timeStep = m_PointListModel->getTimeStep();
            
            if(pointSet->GetNumberOfSelected(timeStep) > 1)
            {
                return;
            }
            
            int selectedIndex = pointSet->SearchSelectedPoint(timeStep);
            
            if(selectedIndex == -1)
            {
                m_SelfCall = false;
                return;
            }
            
            QModelIndex index;
            
            bool modelIndexOkay = m_PointListModel->getModelIndexForPointID(selectedIndex, index);
            
            if(modelIndexOkay)
            {
                this->setSelectedIndex(index.row());
            }
            
            emit this->pointSelectionChanged();
            
            m_SelfCall = false;
        }
        
        void PointListItem::removeSelectedPoint()
        {
            
            if(!m_PointSetNode)
            {
                return;
            }
            mitk::PointSet* pointSet = dynamic_cast<mitk::PointSet*>( m_PointSetNode->GetData());
            if(!pointSet)
            {
                return;
            }
            if(pointSet->GetSize() == 0)
            {
                return;
            }

            this->m_PointListModel->removeSelectedPoint();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            
            emit pointListChanged();
        }
        
        void PointListItem::moveSelectedPointDown()
        {
            
            if(!m_PointSetNode)
            {
                return;
            }
            mitk::PointSet* pointSet = dynamic_cast<mitk::PointSet*>( m_PointSetNode->GetData());
            if(!pointSet)
            {
                return;
            }
            if(pointSet->GetSize() == 0)
            {
                return;
            }

            this->m_PointListModel->moveSelectedPointDown();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            
            emit pointListChanged();
        }
        
        void PointListItem::moveSelectedPointUp()
        {
            
            if(!m_PointSetNode)
            {
                return;
            }
            mitk::PointSet* pointSet = dynamic_cast<mitk::PointSet*>( m_PointSetNode->GetData());
            if(!pointSet)
            {
                return;
            }
            if(pointSet->GetSize() == 0)
            {
                return;
            }

            this->m_PointListModel->moveSelectedPointUp();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            
            emit pointListChanged();
        }
        
        auto PointListItem::getSelectedIndex() -> int
        {
            return this->m_SelectedIndex;
        }
        
        auto PointListItem::setSelectedIndex(int index) -> void
        {
            this->m_SelectedIndex = index;
            this->m_PointListModel->index(index);
            this->onListViewSelectionChanged(index);
            
            emit this->selectedIndexChanged();
        }
        
        void PointListItem::addPoint(bool enabled)
        {
            if(m_PointSetNode.IsNotNull() && enabled)
            {
                m_DataInteractor = m_PointSetNode->GetDataInteractor();
                this->setPointEdit(true);
                
                if(m_DataInteractor.IsNull())
                {
                    m_DataInteractor = mitk::PointSetDataInteractor::New();
                    m_DataInteractor->LoadStateMachine("PointSet.xml");
                    m_DataInteractor->SetEventConfig("PointSetConfig.xml");
                    m_DataInteractor->SetDataNode(m_PointSetNode);
                }
            }
            
            else
            {
                this->disableInteractor();
                this->setPointEdit(false);
            }
        }
        
        auto PointListItem::setPointEdit(bool status) -> void
        {
            this->m_PointEdit = status;
            emit pointEditChanged();
        }
        
        auto PointListItem::resetList() -> void
        {
            this->disableInteractor();
            this->m_PointListModel->setPointSetNode(0);
        }
        
        auto PointListItem::isPointEdit() -> bool
        {
            return this->m_PointEdit;
        }
        
        auto PointListItem::disableInteractor() -> void
        {
            if(m_PointSetNode.IsNotNull())
            {
                
                m_PointSetNode->SetDataInteractor(NULL);
                m_DataInteractor = NULL;
                
                this->setPointEdit(false);
            }
        }
        
        auto PointListItem::updateSelection(mitk::DataNode::Pointer selectedNode) -> void
        {
            this->disableInteractor();
            
            mitk::PointSet* pointSet = 0;
            if(selectedNode)
            {
                pointSet = dynamic_cast<mitk::PointSet*> ( selectedNode->GetData());
            }

            if(pointSet)
            {
                this->setPointSetNode(selectedNode);
            }
            else
            {
                this->setPointSetNode(0);
            }
        }
        
        auto PointListItem::setNodeProperties(mitk::DataNode::Pointer node) -> void
        {
            mitk::PointSet::Pointer pointSet = mitk::PointSet::New();
            node->SetData(pointSet);
            node->SetProperty("name", mitk::StringProperty::New("PointSet"));
            node->SetProperty("opacity", mitk::FloatProperty::New(1));
            node->SetProperty("pointSet", mitk::BoolProperty::New(true));
            node->SetColor(1.0, 1.0, 0.0);
        }
        
        auto PointListItem::observeNewNode(mitk::DataNode* node) -> void
        {
            if(m_DataInteractor.IsNotNull())
            {
                m_DataInteractor->SetDataNode(node);
            }

            if(m_PointSetNode)
            {
                if(m_DataInteractor)
                {
                    m_DataInteractor = NULL;
                    this->setPointEdit(false);
                }

                m_PointSetNode->RemoveObserver(m_NodeObserverTag);
                m_NodeObserverTag = 0;
            }
            
            m_PointSetNode = node;
            
            if(m_PointSetNode)
            {
                itk::ReceptorMemberCommand<PointListItem>::Pointer command = itk::ReceptorMemberCommand<PointListItem>::New();
                command->SetCallbackFunction(this, &PointListItem::onNodeDeleted);
                m_NodeObserverTag = m_PointSetNode->AddObserver(itk::DeleteEvent(), command);
            }
            else
            {
                m_NodeObserverTag = 0;
            }
        }
        
        auto PointListItem::onNodeDeleted(const itk::EventObject &) -> void
        {
            if(m_PointSetNode.IsNotNull() && !m_NodeObserverTag)
            {
                m_PointSetNode->RemoveObserver(m_NodeObserverTag);
            }

            m_NodeObserverTag = 0;
            m_PointSetNode = NULL;
            m_PointListModel->setPointSetNode(NULL);
        }
    }
}