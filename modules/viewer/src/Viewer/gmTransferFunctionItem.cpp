#include "gmTransferFunctionItem.hpp"
#include "gmLog.hpp"
#include "gmDatamanager.hpp"

namespace gm
{
    namespace ViewItem
    {
        TransferFunctionItem* TransferFunctionItem::instance = nullptr;
        
        TransferFunctionItem::TransferFunctionItem(QQuickItem* parent) : QQuickItem(parent), m_max(0), m_min(0), m_currentMin(0), m_currentMax(0)
        {
            if(instance)
            {
                throw ("Instance already existing");
            }
            
            instance = this;
            
            this->setEnabled(false);
            
            setAcceptHoverEvents(true);
            setAcceptedMouseButtons(Qt::AllButtons);
            
            connect(DataManager::instance, &DataManager::notifySelection, this, &TransferFunctionItem::receive);
        }
        
        TransferFunctionItem::~TransferFunctionItem()
        {
        }
        
        void TransferFunctionItem::receive(mitk::DataNode::Pointer node)
        {
            
            if(node && dynamic_cast<mitk::Image*>(node->GetData()) && dynamic_cast<mitk::Image*>(node->GetData())->GetDimension() >= 3)
            {
                this->setDataNode(node);
            }
            else
            {
                //no painting
            }
        }
        
        void TransferFunctionItem::wheelEvent(QWheelEvent* event)
        {
            int fact = -event->delta() * 0.15;
            
            if(event->orientation() == Qt::Horizontal)
            {
                int lower = this->m_currentMin + fact;
                int upper = this->m_currentMax + fact;
                
                if(lower < this->m_min)
                {
                    this->m_currentMin = this->m_min;
                }
                else if(upper > this->m_max)
                {
                    this->m_currentMax = this->m_max;
                }
                else
                {
                    this->m_currentMin = lower;
                    this->m_currentMax = upper;
                }
                emit this->sync();

                updateRanges();
            }
        }
        
        auto TransferFunctionItem::setDataNode(mitk::DataNode* node, const mitk::BaseRenderer* renderer) -> void
        {
            log_trace(Log::Set);
            
            if(node)
            {
                tfpToChange = dynamic_cast<mitk::TransferFunctionProperty*>(node->GetProperty("TransferFunction", renderer));
                
                if(!tfpToChange)
                {
                    if(!dynamic_cast<mitk::Image*>(node->GetData()))
                    {
                        return;
                    }
                    
                    node->SetProperty("TransferFunction", tfpToChange = mitk::TransferFunctionProperty::New());
                }
                
                if(mitk::BaseData* data = node->GetData())
                {
                    mitk::SimpleHistogram* h = m_histogramCache[data];
                    
                    this->setMin(h->GetMin());
                    this->setMax(h->GetMax());
                    
                    this->m_currentMin = h->GetMin();
                    this->m_currentMax = h->GetMax();
                    
                    this->m_colorItem->setHistogram(h);
                    this->m_opacityItem->setHistogram(h);
                    
                    emit this->sync();
                }

                onUpdateCanvas();
                
                return;
            }
        }
        
        void TransferFunctionItem::onUpdateCanvas()
        {
            
            if(tfpToChange.IsNull())
            {
                return;
            }
            
            mitk::TransferFunction::Pointer tf = tfpToChange->GetValue();
            
            if(tf.IsNull())
            {
                return;
            }
            
            this->m_opacityItem->setPiecewiseFunction(tf->GetScalarOpacityFunction());
            this->m_colorItem->setColorTransferFunction(tf->GetColorTransferFunction());

            updateRanges();
            
            this->m_colorItem->update();
            this->m_opacityItem->update();
        }
        
        auto TransferFunctionItem::setColorItem(ColorTransferFunctionCanvas* item) -> void
        {
            log_trace(Log::Set);
            
            this->m_colorItem = item;
        }
        
        auto TransferFunctionItem::getColorItem() -> ColorTransferFunctionCanvas*
        {
            return this->m_colorItem;
        }
        
        auto TransferFunctionItem::setOpactityItem(PiecewiseFunctionCanvas* item) -> void
        {
            log_trace(Log::Set);
            
            this->m_opacityItem = item;
        }
        
        auto TransferFunctionItem::getOpacityItem() -> PiecewiseFunctionCanvas*
        {
            log_trace(Log::Get);
            
            return this->m_opacityItem;
        }
        
        auto TransferFunctionItem::updateRanges() -> void
        {
            int lower = this->m_currentMin;
            int upper = this->m_currentMax;
            
            this->m_opacityItem->setMin(lower);
            this->m_opacityItem->setMax(upper);
            
            this->m_colorItem->setMin(lower);
            this->m_colorItem->setMax(upper);
            
            this->m_opacityItem->update();
            this->m_colorItem->update();
        }
        
        auto TransferFunctionItem::onSpanChanged(int, int) -> void
        {
            updateRanges();
            
            this->m_opacityItem->update();
            this->m_colorItem->update();
        }
        
        auto TransferFunctionItem::onResetSlider() -> void
        {
            this->m_currentMin = this->m_min;
            this->m_currentMax = this->m_max;

            updateRanges();
        }
        
        auto TransferFunctionItem::setMin(double min) -> void
        {
            log_trace(Log::Set);
            
            this->m_min = min;
            emit this->minChanged();
        }
        
        auto TransferFunctionItem::setMax(double max) -> void
        {
            log_trace(Log::Set);
            
            this->m_max = max;
            emit this->maxChanged();
        }
        
        auto TransferFunctionItem::setCurrentMin(double currentMin) -> void
        {
            log_trace(Log::Set);
            
            this->m_currentMin = currentMin;
            updateRanges();
        }
        
        auto TransferFunctionItem::setCurrentMax(double currentMax) -> void
        {
            log_trace(Log::Set);
            
            this->m_currentMax = currentMax;
            updateRanges();
        }
        
        auto TransferFunctionItem::getMin() -> double
        {
            log_trace(Log::Get);
            
            return this->m_min;
        }
        
        auto TransferFunctionItem::getMax() -> double
        {
            log_trace(Log::Get);
            
            return this->m_max;
        }
        
        auto TransferFunctionItem::getCurrentMin() -> double
        {
            log_trace(Log::Get);
            
            return this->m_currentMin;
        }
        
        auto TransferFunctionItem::getCurrentMax() -> double
        {
            log_trace(Log::Get);
            
            return this->m_currentMax;
        }
    }
}