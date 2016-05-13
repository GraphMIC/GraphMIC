#include "gmPropertyController.hpp"

namespace gm
{
    namespace ViewItem
    {
        PropertyController* PropertyController::instance = nullptr;
        
        PropertyController::PropertyController():
        m_volumeRendering(true),
        m_imageNavigator(true),
        m_measurement(true),
        m_pointSet(true),
        m_masking(true),
        m_statistics(true)
        {
            if(instance)
                throw("Instance already existing");

            instance = this;
        }
        
        PropertyController::~PropertyController()
        {
            
        }
        
        auto PropertyController::getVolumeRendering() -> bool
        {
            return this->m_volumeRendering;
        }
        
        auto PropertyController::setVolumeRendering(bool status) -> void
        {
            this->m_volumeRendering = status;
            emit this->volumeRenderingChanged();
        }
        
        auto PropertyController::getImageNavigator() -> bool
        {
            return this->m_imageNavigator;
        }
        
        auto PropertyController::setImageNavigator(bool status) -> void
        {
            this->m_imageNavigator = status;
            emit this->imageNavigatorChanged();
        }
        
        auto PropertyController::getMeasurement() -> bool
        {
            return this->m_measurement;
        }
        
        auto PropertyController::setMeasurement(bool status) -> void
        {
            this->m_measurement = status;
            emit this->measurementChanged();
        }
        
        auto PropertyController::getPointSet() -> bool
        {
            return this->m_pointSet;
        }
        
        auto PropertyController::setPointSet(bool status) -> void
        {
            this->m_pointSet = status;
            emit this->pointSetChanged();
        }
        
        auto PropertyController::getMasking() -> bool
        {
            return this->m_masking;
        }
        
        auto PropertyController::setMasking(bool status) -> void
        {
            this->m_masking = status;
            emit this->maskingChanged();
        }
        
        auto PropertyController::getStatistics() -> bool
        {
            return this->m_statistics;
        }
        
        auto PropertyController::setStatistics(bool status) -> void
        {
            this->m_statistics = status;
            emit this->statisticsChanged();
        }
    }
}