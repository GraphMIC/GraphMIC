#include "gmProperties.hpp"

#include <mitkImage.h>
#include <gmRenderingManager.hpp>
#include <gmTransferFunctionItem.hpp>
#include <gmDatamanager.hpp>
#include <gmPropertyController.hpp>

namespace gm
{
    namespace ViewItem
    {
        VolumeProperties* VolumeProperties::instance = nullptr;
        
        VolumeProperties::VolumeProperties()
        {
            if(instance)
            {
                throw("Instance already existing");
            }

            instance = this;

            connect(DataManager::instance, &DataManager::notifySelection, this, &VolumeProperties::receive);
            connect(this, &VolumeProperties::setStatus, PropertyController::instance, &PropertyController::setVolumeRendering);
        }
        
        VolumeProperties::~VolumeProperties()
        {
        }
        
        auto VolumeProperties::setRendering(bool state) -> void
        {
            this->m_rendering = state;
            if(this->m_node)
            {
                this->m_node->SetBoolProperty("volumerendering", state);
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();

                TransferFunctionItem::instance->onUpdateCanvas();
            }
            
            emit this->renderingChanged();
        }
        
        auto VolumeProperties::setLod(bool state) -> void
        {
            this->m_lod = state;
            if(this->m_node)
            {
                this->m_node->SetBoolProperty("volumerendering.uselod", state);
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
            
            emit this->lodChanged();
        }
        
        auto VolumeProperties::setMode(int mode) -> void
        {
            if(!this->m_node)
            {
                return;
            }
            
            this->m_mode = mode;
            
            bool usegpu = mode == RM_GPU_COMPOSITE_SLICING;

#if ((VTK_MAJOR_VERSION > 5) || ((VTK_MAJOR_VERSION == 5) && (VTK_MINOR_VERSION >= 6)))
            bool useray=(mode==RM_GPU_COMPOSITE_RAYCAST)||(mode==RM_GPU_MIP_RAYCAST);
#endif
            bool usemip = (mode == RM_GPU_MIP_RAYCAST) || (mode == RM_CPU_MIP_RAYCAST);
            
            this->m_node->SetBoolProperty("volumerendering.usegpu", usegpu);

#if ((VTK_MAJOR_VERSION > 5) || ((VTK_MAJOR_VERSION == 5) && (VTK_MINOR_VERSION >= 6)))
            this->m_node->SetBoolProperty("volumerendering.useray",useray);
#endif
            this->m_node->SetBoolProperty("volumerendering.usemip", usemip);
            
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            
            emit this->modeChanged();
        }
        
        auto VolumeProperties::getRendering() -> bool
        {
            return this->m_rendering;
        }
        
        auto VolumeProperties::getLod() -> bool
        {
            return this->m_lod;
        }
        
        auto VolumeProperties::getMode() -> int
        {
            return this->m_mode;
        }
        
        void VolumeProperties::receive(mitk::DataNode::Pointer node)
        {
            if(!node)
            {
                setEnabled(false);
                return;
            }

            bool isImage = false;
            node->GetBoolProperty("image", isImage);
            
            if(isImage && dynamic_cast<mitk::Image*>(node->GetData())->GetDimension() >= 3)
            {
                this->m_node = node;
                emit this->setStatus(true);
                
                if(!this->m_node)
                {
                    this->setEnabled(false);
                    emit this->setStatus(false);
                    emit this->sync();
                    return;
                }
                
                mitk::Image::Pointer image = static_cast<mitk::Image*>(this->m_node->GetData());

                this->setEnabled(image->GetDimension() != 2);
                
                bool use_volumerendering;
                bool use_lod;
                bool use_ray;
                bool use_mip;
                bool use_gpu;
                
                this->m_node->GetBoolProperty("volumerendering", use_volumerendering);
                this->m_node->GetBoolProperty("volumerendering.uselod", use_lod);
                this->m_node->GetBoolProperty("volumerendering.useray", use_ray);
                this->m_node->GetBoolProperty("volumerendering.usemip", use_mip);
                this->m_node->GetBoolProperty("volumerendering.usegpu", use_gpu);
                
                this->setRendering(use_volumerendering);
                this->setLod(use_lod);
                
                int mode = 0;
                
                if(use_ray)
                {
                    if(use_mip)
                    {
                        mode = RM_GPU_MIP_RAYCAST;
                    }
                    else
                    {
                        mode = RM_GPU_COMPOSITE_RAYCAST;
                    }
                }
                else if(use_gpu)
                {
                    mode = RM_GPU_COMPOSITE_SLICING;
                }
                else
                {
                    if(use_mip)
                    {
                        mode = RM_CPU_MIP_RAYCAST;
                    }
                    else
                    {
                        mode = RM_CPU_COMPOSITE_RAYCAST;
                    }
                }
                
                this->setMode(mode);
            }
            else
            {
                setEnabled(false);
                emit this->setStatus(false);
            }
            
            emit this->sync();
        }
    }
}

