#include "gmMaskingItem.hpp"
#include "gmDatamanager.hpp"
#include "gmPropertyController.hpp"
#include <mitkToolManagerProvider.h>
#include <mitkLiveWireTool2D.h>
#include <mitkDisplayInteractor.h>
#include <mitkPaintbrushTool.h>
#include <mitkErasePaintbrushTool.h>
#include <mitkMaskImageFilter.h>
#include <mitkImageStatisticsHolder.h>
#include <mitkLabelSetImage.h>
#include <mitkLookupTableProperty.h>
#include <mitkLevelWindowProperty.h>
#include <mitkVtkResliceInterpolationProperty.h>
#include <usModuleRegistry.h>
#include <usGetModuleContext.h>
#include <usModuleInitialization.h>

US_INITIALIZE_MODULE

namespace gm
{
    namespace ViewItem
    {
        MaskingItem* MaskingItem::instance = nullptr;
        
        MaskingItem::MaskingItem()
        {
            if(instance)
            {
                throw ("Instance already existing");
            }
            instance = this;
            
            this->m_toolManager = mitk::ToolManager::New(storage.GetPointer());
            this->m_toolManager->InitializeTools();
            this->m_registeredClients = 0;
            this->setEnabled(false);
            
            mitk::ToolManager::ToolVectorTypeConst allPossibleTools = this->m_toolManager->GetTools();
            for(auto iter = allPossibleTools.begin(); iter != allPossibleTools.end(); ++iter)
            {
                try
                {
                    const mitk::Tool* tool = *iter;
                    m_toolHash[tool->GetName()] = const_cast<mitk::Tool*>(tool);
                }
                catch(...)
                {
                    
                }
            }
            
            connect(DataManager::instance, &DataManager::notifySelection, this, &MaskingItem::receive);
            connect(this, &MaskingItem::setStatus, PropertyController::instance, &PropertyController::setMasking);
        }
        
        MaskingItem::~MaskingItem()
        {
            
        }
        
        void MaskingItem::receive(mitk::DataNode::Pointer node)
        {
            if(!node)
            {
                setEnabled(false);
                emit this->setStatus(false);
                return;
            }

            bool isMasking = false;
            node->GetBoolProperty("masking", isMasking);
            mitk::LabelSetImage* labelSetImage = dynamic_cast<mitk::LabelSetImage*>(node->GetData());
            
            if(isMasking && !labelSetImage)
            {
                setEnabled(true);
                this->m_node = node;
                this->createNewMask(node);
                emit this->setStatus(true);
            }
            else if(isMasking && labelSetImage)
            {
                setEnabled(true);
                this->m_node = node;
                this->initNode(node);
                emit this->setStatus(true);
            }
            else
            {
                setEnabled(false);
                deactivateTool();
                emit this->setStatus(false);
            }
        }
        
        auto MaskingItem::SetDataStorage(mitk::DataStorage::Pointer dataStorage) -> void
        {
            storage = dataStorage;
        }
        
        auto MaskingItem::setNodeProperties(mitk::DataNode::Pointer node) -> void
        {
            node->SetName("Masking");
            node->SetProperty("masking", mitk::BoolProperty::New(true));
        }
        
        auto MaskingItem::initNode(mitk::DataNode::Pointer node) -> void
        {
            mitk::DataStorage::SetOfObjects::ConstPointer sourceNodes = storage->GetSources(node);
            if(sourceNodes.IsNull() || sourceNodes->size() > 1)
            {
                throw("Wrong initialization");
            }
            this->deactivateTool();

            
            this->m_toolManager->SetReferenceData(sourceNodes->at(0));
            this->m_toolManager->SetWorkingData(node);
        }
        
        /*
         auto MaskingItem::createNewMask(mitk::DataNode::Pointer node) -> void
         {
         mitk::Image* image = dynamic_cast<mitk::Image*>(node->GetData());
         
         if(node.IsNull() && !image)
         {
         return;
         }
         
         this->m_toolManager->SetReferenceData(node);
         mitk::Tool* firstTool = this->m_toolManager->GetToolById(0);
         
         if(firstTool)
         {
         mitk::Color color;
         color.SetRed(1);
         color.SetBlue(0);
         color.SetGreen(0);
         
         mitk::DataNode::Pointer emptySegmentation = firstTool->CreateEmptySegmentationNode(image, "Segmentation", color);
         
         emptySegmentation->SetProperty("showVolume", mitk::BoolProperty::New(false));
         emptySegmentation->SetSelected(false);
         emptySegmentation->SetProperty("masking", mitk::BoolProperty::New(true));
         
         this->m_toolManager->SetWorkingData(emptySegmentation);
         
         storage->Add(emptySegmentation, node);
         }
         }*/
        
        
        auto MaskingItem::createNewMask(mitk::DataNode::Pointer node) -> void
        {
            
            mitk::DataStorage::SetOfObjects::ConstPointer sourceNodes = storage->GetSources(node);
            if(sourceNodes.IsNull() || sourceNodes->size() > 1)
            {
                throw("Wrong initialization");
            }
            
            mitk::DataNode::Pointer parentNode = sourceNodes->at(0);
            mitk::Image* image = dynamic_cast<mitk::Image*>(parentNode->GetData());
            
            if(parentNode.IsNull() && !image)
            {
                return;
            }
            
            this->m_toolManager->SetReferenceData(parentNode);
            mitk::Tool* firstTool = this->m_toolManager->GetToolById(0);
            
            if(firstTool)
            {
                mitk::Color color;
                color.SetRed(1);
                color.SetBlue(0);
                color.SetGreen(0);
                
                node->SetData(firstTool->CreateEmptySegmentationNode(image, "Masking", color)->GetData());
                node->SetProperty( "binary", mitk::BoolProperty::New(true) );
                mitk::LookupTable::Pointer lut = mitk::LookupTable::New();
                lut->SetType(mitk::LookupTable::MULTILABEL);
                mitk::LookupTableProperty::Pointer lutProp = mitk::LookupTableProperty::New();
                lutProp->SetLookupTable(lut);
                node->SetProperty("LookupTable", lutProp);
                node->SetProperty("texture interpolation", mitk::BoolProperty::New(false) );
                node->SetProperty("layer", mitk::IntProperty::New(10) );
                node->SetProperty("levelwindow", mitk::LevelWindowProperty::New(mitk::LevelWindow(0.5, 1)));
                node->SetProperty("opacity", mitk::FloatProperty::New(0.3) );
                node->SetProperty("segmentation", mitk::BoolProperty::New(true) );
                node->SetProperty("reslice interpolation", mitk::VtkResliceInterpolationProperty::New());
                node->SetProperty("showVolume", mitk::BoolProperty::New(false));
                
                this->m_toolManager->SetWorkingData(node);
            }
        }
        
        auto MaskingItem::getToolIdByString(QString id) -> int
        {
            mitk::Tool* tool = m_toolHash.value(id);
            
            return this->m_toolManager->GetToolID(tool);
        }
        
        void MaskingItem::activateTool(QString idx)
        {
            if(this->m_toolManager->GetActiveTool() == NULL)
            {
                this->m_toolManager->RegisterClient();
            }
            
            this->m_toolManager->ActivateTool(getToolIdByString(idx));
            this->updateInputs();
        }
        
        auto MaskingItem::setSliderEnabled(bool status) -> void
        {
            this->m_sliderEnabled = status;
            emit this->sliderEnabledChanged();
        }
        
        auto MaskingItem::isSliderEnabled() -> bool
        {
            return this->m_sliderEnabled;
        }
        
        auto MaskingItem::setSliderSize(int size) -> void
        {
            mitk::Tool* tool = this->m_toolManager->GetActiveTool();
            
            if(!tool)
            {
                return;
            }
            
            QString toolName = tool->GetName();
            
            if(toolName == "Paint")
            {
                dynamic_cast<mitk::PaintbrushTool*>( tool )->SetSize(size);
            }
            else if(toolName == "Wipe")
            {
                dynamic_cast<mitk::ErasePaintbrushTool*>( tool )->SetSize(size);
            }
            
            this->m_sliderSize = size;
            emit this->sliderSizeChanged();
        }
        
        auto MaskingItem::getSliderSize() -> int
        {
            return this->m_sliderSize;
        }
        
        auto MaskingItem::updateInputs() -> void
        {
            mitk::Tool* tool = this->m_toolManager->GetActiveTool();
            
            QString toolName = tool->GetName();
            QStringList toolOptions{"Paint", "Wipe"};
            
            if(toolOptions.contains(toolName))
            {
                this->setSliderEnabled(true);
            }
        }
        
        void MaskingItem::confirmMask()
        {
            mitk::DataNode::Pointer node = this->m_node;
            mitk::DataStorage::SetOfObjects::ConstPointer sourceNodes = storage->GetSources(node);
            mitk::DataNode::Pointer sourceNode = sourceNodes->front();
            
            if(node.IsNull() || sourceNode.IsNull())
            {
                return;
            }
            
            mitk::Image* referenceImage = dynamic_cast<mitk::Image*>(sourceNode->GetData());
            mitk::Image* maskImage = dynamic_cast<mitk::Image*>(node->GetData());
            
            if(!referenceImage && !maskImage)
            {
                return;
            }
            
            mitk::Image::Pointer resultImage(nullptr);
            
            if(referenceImage->GetLargestPossibleRegion().GetSize() == maskImage->GetLargestPossibleRegion().GetSize())
            {
                resultImage = this->maskImage(referenceImage, maskImage);
            }
            
            if(resultImage.IsNull())
            {
                return;
            }
            
            mitk::DataNode::Pointer resultNode = mitk::DataNode::New();
            resultNode->SetData(resultImage);
            resultNode->SetName(node->GetName() + "_" + sourceNode->GetName());
            resultNode->SetBoolProperty("image", true);
            storage->Add(resultNode);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto MaskingItem::addToDataStorage(mitk::Image::Pointer segmentation, const std::string &name, mitk::DataNode::Pointer parent) -> void
        {
            mitk::DataNode::Pointer dataNode = mitk::DataNode::New();
            
            dataNode->SetName(name);
            dataNode->SetData(segmentation);
            
            storage->Add(dataNode, parent);
        }
        
        auto MaskingItem::maskImage(mitk::Image::Pointer referenceImage, mitk::Image::Pointer maskImage) -> mitk::Image::Pointer
        {
            mitk::Image::Pointer resultImage(nullptr);
            
            mitk::MaskImageFilter::Pointer maskFilter = mitk::MaskImageFilter::New();
            maskFilter->SetInput(referenceImage);
            maskFilter->SetMask(maskImage);
            maskFilter->OverrideOutsideValueOn();
            maskFilter->SetOutsideValue(referenceImage->GetStatistics()->GetScalarValueMin());
            try
            {
                maskFilter->Update();
            }
            catch(itk::ExceptionObject &excpt)
            {
                return nullptr;
            }
            
            resultImage = maskFilter->GetOutput();
            
            return resultImage;
        }
        
        auto MaskingItem::deactivateTool() -> void
        {
            if(this->m_toolManager->GetActiveTool() == NULL)
                return;
            
            this->m_toolManager->ActivateTool(-1);
            this->m_toolManager->UnregisterClient();
            
            std::vector<us::ServiceReference<mitk::InteractionEventObserver> > listEventObserver = us::GetModuleContext()->GetServiceReferences<mitk::InteractionEventObserver>();
            for(std::vector<us::ServiceReference<mitk::InteractionEventObserver> >::iterator it = listEventObserver.begin();
                it != listEventObserver.end(); ++it)
            {
                mitk::DisplayInteractor* displayInteractor = dynamic_cast<mitk::DisplayInteractor*>(us::GetModuleContext()->GetService<mitk::InteractionEventObserver>(*it));
                if(displayInteractor != NULL)
                {
                    displayInteractor->SetEventConfig("DisplayConfigMITK.xml");
                }
            }
        }
        
        void MaskingItem::deactivateTool(QString idx)
        {
            if(this->m_toolManager->GetActiveTool()->GetName() != idx)
                return;
            
            deactivateTool();
        }
    }
}