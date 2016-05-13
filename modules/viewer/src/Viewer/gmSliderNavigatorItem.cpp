#include "gmSliderNavigatorItem.hpp"

namespace gm
{
    namespace ViewItem
    {
        SliderNavigatorItem::SliderNavigatorItem(QQuickItem* parent) :
        QQuickItem(parent),
        m_inRefetch(true),
        m_hasLabels(false),
        m_hasLabelUnit(true),
        m_inverseDirection(false)
        {
        }
        
        SliderNavigatorItem::~SliderNavigatorItem()
        {
        }
        
        auto SliderNavigatorItem::setMin(double min) -> void
        {
            this->m_min = min;
        }
        
        auto SliderNavigatorItem::setMax(double max) -> void
        {
            this->m_max = max;
        }
        
        auto SliderNavigatorItem::setValue(double value) -> void
        {
            this->m_value = value;
            
            if(!m_inRefetch)
            {
                if(m_inverseDirection)
                {
                    m_stepper->SetPos(m_stepper->GetSteps() - 1 - value);
                }
                else
                {
                    m_stepper->SetPos(value);
                }
                this->Refetch();
            }
        }
        
        auto SliderNavigatorItem::getMax() -> double
        {
            return this->m_max;
        }
        
        auto SliderNavigatorItem::getMin() -> double
        {
            return this->m_min;
        }
        
        auto SliderNavigatorItem::getValue() -> double
        {
            return this->m_value;
        }
        
        auto SliderNavigatorItem::Refetch() -> void
        {
            if(!m_inRefetch)
            {
                m_inRefetch = true;
                
                this->m_min = 0;
                this->m_max = m_stepper->GetSteps() - 1;
                
                if(m_inverseDirection)
                {
                    this->m_value = m_stepper->GetSteps() - 1 - m_stepper->GetPos();
                }
                else
                {
                    this->m_value = m_stepper->GetPos();
                }
                
                m_inRefetch = false;
                
                emit this->sync();
            }
        }
        
        auto SliderNavigatorItem::SetStepper(mitk::Stepper* stepper) -> void
        {
            m_stepper = stepper;
            m_inRefetch = (stepper == nullptr);
        }
        
        auto SliderNavigatorItem::getLabelUnit() -> QString
        {
            return m_labelUnit;
        }
        
        auto SliderNavigatorItem::clippedValueToString(float value) -> QString
        {
            if(value < -10000000.0)
            {
                return "-INF";
            }
            else if(value > 10000000.0)
            {
                return "+INF";
            }
            else
            {
                return QString::number(value, 'f', 2);
            }
        }
        
        auto SliderNavigatorItem::getMinValueLabel() -> QString
        {
            if(m_minValueValid)
            {
                return this->clippedValueToString(m_minValue);
            }
            else
            {
                return "N/A";
            }
        }
        
        QString SliderNavigatorItem::getMaxValueLabel()
        {
            if(m_maxValueValid)
            {
                return this->clippedValueToString(m_maxValue);
            }
            else
            {
                return "N/A";
            }
        }
        
        auto SliderNavigatorItem::getPos() -> int
        {
            return m_stepper->GetPos();
        }
        
        void SliderNavigatorItem::setPos(int val)
        {
            if(!m_inRefetch)
            {
                m_stepper->SetPos(val);
            }
        }
        
        void SliderNavigatorItem::setInverseDirection(bool inverseDirection)
        {
            m_inverseDirection = inverseDirection;
        }
        
        void SliderNavigatorItem::showLabels(bool show)
        {
            m_hasLabels = show;
        }
        
        void SliderNavigatorItem::showLabelUnit(bool show)
        {
            m_hasLabelUnit = show;
        }
        
        void SliderNavigatorItem::setLabelValues(float min, float max)
        {
            m_minValue = min;
            m_maxValue = max;
        }
        
        void SliderNavigatorItem::setLabelValuesValid(bool minValid, bool maxValid)
        {
            m_minValueValid = minValid;
            m_maxValueValid = maxValid;
        }
        
        void SliderNavigatorItem::setLabelUnit(const char* unit)
        {
            m_labelUnit = unit;
        }
    }
}

