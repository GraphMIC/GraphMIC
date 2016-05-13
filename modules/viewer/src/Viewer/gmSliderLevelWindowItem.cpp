#include <gmSliderLevelWindowItem.hpp>
#include <QCursor>
#include <QPainter>

#include <itkCommand.h>
#include <mitkRenderingManager.h>

namespace gm
{
    namespace ViewItem
    {
        SliderLevelWindowItem* SliderLevelWindowItem::instance = nullptr;
        
        mitk::DataStorage::Pointer SliderLevelWindowItem::storage = nullptr;
        
        SliderLevelWindowItem::SliderLevelWindowItem(QQuickPaintedItem* parent) : QQuickPaintedItem(parent),
        m_resize(false),
        m_bottom(false),
        m_ctrlPressed(false),
        m_mouseDown(false),
        m_scaleVisible(false),
        m_isObserverTagSet(true)
        {
            m_Manager = mitk::LevelWindowManager::New();
            m_Manager->SetDataStorage(SliderLevelWindowItem::storage);
            
            itk::ReceptorMemberCommand<SliderLevelWindowItem>::Pointer command = itk::ReceptorMemberCommand<SliderLevelWindowItem>::New();
            command->SetCallbackFunction(this, &SliderLevelWindowItem::onPropertyModified);
            m_observerTag = m_Manager->AddObserver(itk::ModifiedEvent(), command);
            
            setAcceptedMouseButtons(Qt::AllButtons);
            setAcceptHoverEvents(true);
            setAntialiasing(false);
            
            this->setEnabled(false);
            
            update();
        }
        
        SliderLevelWindowItem::~SliderLevelWindowItem()
        {
            if(m_isObserverTagSet)
            {
                m_Manager->RemoveObserver(m_observerTag);
                m_isObserverTagSet = false;
            }
        }
        
        void SliderLevelWindowItem::setLevelWindowManager(mitk::LevelWindowManager* levelWindowManager)
        {
            if(m_isObserverTagSet)
            {
                m_Manager->RemoveObserver(m_observerTag);
                m_isObserverTagSet = false;
            }
            m_Manager = levelWindowManager;
            if(m_Manager.IsNotNull())
            {
                itk::ReceptorMemberCommand<SliderLevelWindowItem>::Pointer command = itk::ReceptorMemberCommand<SliderLevelWindowItem>::New();
                command->SetCallbackFunction(this, &SliderLevelWindowItem::onPropertyModified);
                m_observerTag = m_Manager->AddObserver(itk::ModifiedEvent(), command);
                m_isObserverTagSet = true;
            }
        }
        
        void SliderLevelWindowItem::onPropertyModified(const itk::EventObject &)
        {
            try
            {
                m_LevelWindow = m_Manager->GetLevelWindow();
                
                this->m_level = (int) m_LevelWindow.GetLevel();
                this->m_window = (int) m_LevelWindow.GetWindow();
                this->setEnabled(true);
                
                emit this->sync();
                update();
            }
            catch(...)
            {
                this->setEnabled(false);
            }
            
            QQuickPaintedItem::update();
        }
        
        bool SliderLevelWindowItem::isEnabled()
        {
            return this->m_enabled;
        }
        
        void SliderLevelWindowItem::setEnabled(bool enable)
        {
            this->m_enabled = enable;
            emit this->enabledChanged();
        }
        
        auto SliderLevelWindowItem::fontSize() -> int const
        {
            return this->m_fontSize;
        }
        
        void SliderLevelWindowItem::setFontSize(const int &fontSize)
        {
            this->m_fontSize = fontSize;
            this->m_font.setPointSize(fontSize);
        }
        
        auto SliderLevelWindowItem::fontColor() -> QColor const
        {
            return this->m_fontColor;
        }
        
        void SliderLevelWindowItem::setFontColor(const QColor &color)
        {
            this->m_fontColor = color;
        }
        
        auto SliderLevelWindowItem::color() -> QColor const
        {
            return this->m_color;
        }
        
        auto SliderLevelWindowItem::setColor(const QColor &color) -> void
        {
            this->m_color = color;
        }
        
        auto SliderLevelWindowItem::borderColor() -> QColor const
        {
            return this->m_borderColor;
        }
        
        auto SliderLevelWindowItem::setBorderColor(const QColor &color) -> void
        {
            this->m_borderColor = color;
        }
        
        auto SliderLevelWindowItem::setLevel(int level) -> void
        {
            
            if(level != m_LevelWindow.GetLevel())
            {
                m_LevelWindow.SetLevelWindow(level, m_LevelWindow.GetWindow());
                m_Manager->SetLevelWindow(m_LevelWindow);
                
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
            
            this->m_level = level;
        }
        
        auto SliderLevelWindowItem::getLevel() -> int
        {
            return this->m_level;
        }
        
        auto SliderLevelWindowItem::setWindow(int window) -> void
        {
            
            if(window != m_LevelWindow.GetWindow())
            {
                m_LevelWindow.SetLevelWindow(m_LevelWindow.GetLevel(), window);
                m_Manager->SetLevelWindow(m_LevelWindow);
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
            
            this->m_window = window;
        }
        
        auto SliderLevelWindowItem::getWindow() -> int
        {
            return this->m_window;
        }
        
        auto SliderLevelWindowItem::paint(QPainter* painter) -> void
        {
            if(!this->m_enabled)
            {
                return;
            }
            
            m_moveHeight = boundingRect().height() - 55;
            
            painter->setFont(m_font);
            painter->setPen(this->m_borderColor);
            
            painter->setBrush(this->m_color);
            painter->drawRoundedRect(m_rect, 2, 2);
            
            painter->setPen(this->m_fontColor);
            
            float mr = m_LevelWindow.GetRange();
            
            if(mr < 1)
            {
                mr = 1;
            }
            
            float fact = (float) m_moveHeight / mr;
            
            //begin draw scale

            int minRange = (int) m_LevelWindow.GetRangeMin();
            int maxRange = (int) m_LevelWindow.GetRangeMax();
            int yValue = m_moveHeight + (int) (minRange * fact);
            QString s = " 0";
            if(minRange <= 0 && maxRange >= 0)
            {
                painter->drawLine(5, yValue, 15, yValue);
                painter->drawText(21, yValue + 3, s);
            }

            int count = 1;
            int k = 5;
            bool enoughSpace = false;
            bool enoughSpace2 = false;

            double dStepSize = pow(10, floor(log10(mr / 100)) + 1);

            for(int i = m_moveHeight + (int) (minRange * fact); i < m_moveHeight;)
            {
                if(-count * dStepSize < minRange)
                {
                    break;
                }
                yValue = m_moveHeight + (int) ((minRange + count * dStepSize) * fact);

                s = QString::number(-count * dStepSize);
                if(count % k && ((dStepSize * fact) > 2.5))
                {
                    painter->drawLine(8, yValue, 12, yValue);
                    enoughSpace = true;
                }
                else if(!(count % k))
                {
                    if((k * dStepSize * fact) > 7)
                    {
                        painter->drawLine(5, yValue, 15, yValue);
                        painter->drawText(21, yValue + 3, s);
                        enoughSpace2 = true;
                    }
                    else
                    {
                        k += 5;
                    }
                }
                if(enoughSpace)
                {
                    i = yValue;
                    count++;
                }
                else if(enoughSpace2)
                {
                    i = yValue;
                    count += k;
                }
                else
                {
                    i = yValue;
                    count = k;
                }
            }
            count = 1;
            k = 5;
            enoughSpace = false;
            enoughSpace2 = false;

            for(int i = m_moveHeight + (int) (minRange * fact); i >= 0;)
            {
                if(count * dStepSize > maxRange)
                {
                    break;
                }
                yValue = m_moveHeight + (int) ((minRange - count * dStepSize) * fact);

                s = QString::number(count * dStepSize);
                if(count % k && ((dStepSize * fact) > 2.5))
                {
                    if(!(minRange > 0 && (count * dStepSize) < minRange))
                    {
                        painter->drawLine(8, yValue, 12, yValue);
                    }
                    enoughSpace = true;
                }
                else if(!(count % k))
                {
                    if((k * dStepSize * fact) > 7)
                    {
                        if(!(minRange > 0 && (count * dStepSize) < minRange))
                        {
                            painter->drawLine(5, yValue, 15, yValue);
                            painter->drawText(21, yValue + 3, s);
                        }
                        enoughSpace2 = true;
                    }
                    else
                    {
                        k += 5;
                    }
                }
                if(enoughSpace)
                {
                    i = yValue;
                    count++;
                }
                else if(enoughSpace2)
                {
                    i = yValue;
                    count += k;
                }
                else
                {
                    i = yValue;
                    count = k;
                }
            }
        }
        
        auto SliderLevelWindowItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) -> void
        {
            update();
            QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);
        }
        
        auto SliderLevelWindowItem::hoverMoveEvent(QHoverEvent* mouseEvent) -> void
        {
            if(mouseEvent->pos().y() >= 0 && mouseEvent->pos().y() <= (m_rect.topLeft().y() + 3))
            {
                setCursor(Qt::SizeVerCursor);
                m_upperBound.setRect(m_rect.topLeft().x(), m_rect.topLeft().y() - 3, 17, 7);
                //this->setToolTip("Ctrl + left click to change only upper bound");
                m_resize = true;
            }
            else if(mouseEvent->pos().y() >= (m_rect.bottomLeft().y() - 3))
            {
                setCursor(Qt::SizeVerCursor);
                m_lowerBound.setRect(m_rect.bottomLeft().x(), m_rect.bottomLeft().y() - 3, 17, 7);
                //this->setToolTip("Ctrl + left click to change only lower bound");
                m_resize = true;
                m_bottom = true;
            }
            else
            {
                setCursor(Qt::ArrowCursor);
                //this->setToolTip("Left click and mouse move to adjust the slider");
                m_resize = false;
                m_bottom = false;
            }
        }
        /**
         *
         */
        auto SliderLevelWindowItem::mouseMoveEvent(QMouseEvent* mouseEvent) -> void
        {
            if(!mouseEvent && !m_mouseDown)
            {
                return;
            }
            if(m_LevelWindow.IsFixed())
            {
                return;
            }
            
            float fact = (float) m_moveHeight / m_LevelWindow.GetRange();
            
            if(m_leftbutton)
            {
                if(m_resize && !m_ctrlPressed)
                {
                    double diff = (mouseEvent->pos().y()) / fact;
                    diff -= (m_startPos.y()) / fact;
                    m_startPos = mouseEvent->pos();
                    
                    if(diff == 0)
                    {
                        return;
                    }
                    float value;
                    if(m_bottom)
                    {
                        value = m_LevelWindow.GetWindow() + ((2 * diff));
                    }
                    else
                    {
                        value = m_LevelWindow.GetWindow() - ((2 * diff));
                    }
                    
                    if(value < 0)
                    {
                        value = 0;
                    }
                    
                    m_LevelWindow.SetLevelWindow(m_LevelWindow.GetLevel(), value);
                }
                else if(m_resize && m_ctrlPressed)
                {
                    if(!m_bottom)
                    {
                        double diff = (mouseEvent->pos().y()) / fact;
                        diff -= (m_startPos.y()) / fact;
                        m_startPos = mouseEvent->pos();
                        
                        if(diff == 0)
                        {
                            return;
                        }
                        float value;
                        
                        value = m_LevelWindow.GetWindow() - ((diff));
                        
                        if(value < 0)
                        {
                            value = 0;
                        }
                        float oldWindow;
                        float oldLevel;
                        float newLevel;
                        oldWindow = m_LevelWindow.GetWindow();
                        oldLevel = m_LevelWindow.GetLevel();
                        newLevel = oldLevel + (value - oldWindow) / 2;
                        if(newLevel + value / 2 <= m_LevelWindow.GetRangeMax())
                        {
                            m_LevelWindow.SetLevelWindow(newLevel, value);
                        }
                    }
                    else
                    {
                        double diff = (mouseEvent->pos().y()) / fact;
                        diff -= (m_startPos.y()) / fact;
                        m_startPos = mouseEvent->pos();
                        
                        if(diff == 0)
                        {
                            return;
                        }
                        float value;
                        
                        value = m_LevelWindow.GetWindow() + ((diff));
                        
                        if(value < 0)
                        {
                            value = 0;
                        }
                        float oldWindow;
                        float oldLevel;
                        float newLevel;
                        oldWindow = m_LevelWindow.GetWindow();
                        oldLevel = m_LevelWindow.GetLevel();
                        newLevel = oldLevel - (value - oldWindow) / 2;
                        if(newLevel - value / 2 >= m_LevelWindow.GetRangeMin())
                        {
                            m_LevelWindow.SetLevelWindow(newLevel, value);
                        }
                    }
                }
                else
                {
                    const float minv = m_LevelWindow.GetRangeMin();
                    
                    const float level = (m_moveHeight - mouseEvent->pos().y()) / fact + minv;
                    
                    double diff = (mouseEvent->pos().x()) / fact;
                    diff -= (m_startPos.x()) / fact;
                    m_startPos = mouseEvent->pos();
                    
                    float window;
                    if(m_bottom)
                    {
                        window = m_LevelWindow.GetWindow() + ((2 * diff));
                    }
                    else
                    {
                        window = m_LevelWindow.GetWindow() - ((2 * diff));
                    }
                    
                    if(window < 0)
                    {
                        window = 0;
                    }
                    
                    m_LevelWindow.SetLevelWindow(level, window);
                }
                m_Manager->SetLevelWindow(m_LevelWindow);
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
            
        }
        
        auto SliderLevelWindowItem::mousePressEvent(QMouseEvent* mouseEvent) -> void
        {
            if(m_LevelWindow.IsFixed())
            {
                return;
            }
            m_mouseDown = true;
            m_startPos = mouseEvent->pos();
            
            if(mouseEvent->button() == Qt::LeftButton)
            {
                m_ctrlPressed = mouseEvent->modifiers() == Qt::ControlModifier || mouseEvent->modifiers() == Qt::ShiftModifier;
                m_leftbutton = true;
            }
            else
            {
                m_leftbutton = false;
            }
            
            mouseMoveEvent(mouseEvent);
        }
        
        auto SliderLevelWindowItem::mouseReleaseEvent(QMouseEvent*) -> void
        {
            if(m_LevelWindow.IsFixed())
            {
                return;
            }
            m_mouseDown = false;
        }
        
        auto SliderLevelWindowItem::update() -> void
        {
            int rectWidth = 16;

            float mr = m_LevelWindow.GetRange();
            
            if(mr < 1)
            {
                mr = 1;
            }
            
            float fact = (float) m_moveHeight / mr;
            
            float rectHeight = m_LevelWindow.GetWindow() * fact;
            
            if(rectHeight < 15)
            {
                rectHeight = 15;
            }
            
            if(m_LevelWindow.GetLowerWindowBound() < 0)
            {
                m_rect.setRect(2, (int) (m_moveHeight - (m_LevelWindow.GetUpperWindowBound() - m_LevelWindow.GetRangeMin()) * fact), rectWidth, (int) rectHeight);
            }
            else
            {
                m_rect.setRect(2, (int) (m_moveHeight - (m_LevelWindow.GetUpperWindowBound() - m_LevelWindow.GetRangeMin()) * fact), rectWidth, (int) rectHeight);
            }
            
            QQuickPaintedItem::update();
        }
        
        auto SliderLevelWindowItem::hideScale() -> void
        {
            m_scaleVisible = false;
            update();
        }
        
        auto SliderLevelWindowItem::showScale() -> void
        {
            m_scaleVisible = true;
            update();
        }
        
        auto SliderLevelWindowItem::SetDataStorage(mitk::DataStorage* ds) -> void
        {
            storage = ds;
        }
        
        auto SliderLevelWindowItem::getManager() -> mitk::LevelWindowManager*
        {
            return m_Manager.GetPointer();
        }
    }
}