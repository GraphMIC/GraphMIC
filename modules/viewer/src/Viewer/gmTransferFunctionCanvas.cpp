#include "gmTransferFunctionCanvas.hpp"
#include <QColorDialog>
#include <QPainter>

namespace gm
{
    namespace ViewItem
    {
        TransferFunctionCanvas::TransferFunctionCanvas(QQuickPaintedItem* parent) : QQuickPaintedItem(parent), m_immediateUpdate(false), m_range(0.0f), m_grabbedHandle(-1), m_lower(0.0), m_upper(1.0), m_min(0.0), m_max(1.0), m_histogram(nullptr)
        {
            setAcceptedMouseButtons(Qt::AllButtons);
            setAcceptHoverEvents(true);
            setAntialiasing(true);
        }
        
        TransferFunctionCanvas::~TransferFunctionCanvas()
        {
            
        }
        
        auto TransferFunctionCanvas::functionToCanvas(std::pair<double, double> functionPoint) -> std::pair<int, int>
        {
            return std::make_pair((int) ((functionPoint.first - m_lower) / (m_upper - m_lower) * boundingRect().width()) + boundingRect().x(), (int) (boundingRect().height() * (1 - functionPoint.second)) + boundingRect().y());
        }
        
        auto TransferFunctionCanvas::canvasToFunction(std::pair<int, int> canvasPoint) -> std::pair<double, double>
        {
            return std::make_pair((canvasPoint.first - boundingRect().x()) * (m_upper - m_lower) / boundingRect().width() + m_lower, 1.0 - (double) (canvasPoint.second - boundingRect().y()) / boundingRect().height());
        }
        
        auto TransferFunctionCanvas::mouseDoubleClickEvent(QMouseEvent* mouseEvent) -> void
        {
            int nearHandle = getNearHandle(mouseEvent->pos().x(), mouseEvent->pos().y());
            if(nearHandle != -1)
            {
                this->doubleClickOnHandle(nearHandle);
            }
        }

        auto TransferFunctionCanvas::getNearHandle(int, int, unsigned int) -> int
        {
            return -1;
        }
        
        auto TransferFunctionCanvas::mousePressEvent(QMouseEvent* mouseEvent) -> void
        {
            forceActiveFocus();
            
            if(mouseEvent->button() == Qt::RightButton)
            {
                mouseEvent->setAccepted(false);
            }

            m_grabbedHandle = getNearHandle(mouseEvent->pos().x(), mouseEvent->pos().y());

            if((mouseEvent->button() & Qt::LeftButton) && m_grabbedHandle == -1)
            {
                this->addFunctionPoint(this->canvasToFunction(std::make_pair(mouseEvent->pos().x(), mouseEvent->pos().y())).first, this->canvasToFunction(std::make_pair(mouseEvent->x(), mouseEvent->y())).second);
                m_grabbedHandle = getNearHandle(mouseEvent->pos().x(), mouseEvent->pos().y());

                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
            
            update();
        }
        
        auto TransferFunctionCanvas::mouseMoveEvent(QMouseEvent* mouseEvent) -> void
        {
            if(m_grabbedHandle != -1)
            {
                std::pair<double, double> newPos = this->canvasToFunction(std::make_pair(mouseEvent->x(), mouseEvent->y()));

                {
                    if(m_grabbedHandle > 0)
                    {
                        if(newPos.first <= this->getFunctionX(m_grabbedHandle - 1))
                        {
                            newPos.first = this->getFunctionX(m_grabbedHandle);
                        }
                    }

                    if(m_grabbedHandle < this->getFunctionSize() - 1)
                    {
                        if(newPos.first >= this->getFunctionX(m_grabbedHandle + 1))
                        {
                            newPos.first = this->getFunctionX(m_grabbedHandle);
                        }
                    }

                    if(newPos.first < m_min)
                    {
                        newPos.first = m_min;
                    }
                    else if(newPos.first > m_max)
                    {
                        newPos.first = m_max;
                    }
                }

                {
                    if(newPos.second < 0.0)
                    {
                        newPos.second = 0.0;
                    }
                    else if(newPos.second > 1.0)
                    {
                        newPos.second = 1.0;
                    }
                }

                this->moveFunctionPoint(m_grabbedHandle, newPos);
                
                update();
                
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
        }
        
        auto TransferFunctionCanvas::mouseReleaseEvent(QMouseEvent*) -> void
        {
            update();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto TransferFunctionCanvas::paintHistogram(QPainter* p) -> void
        {
            if(m_histogram)
            {
                p->save();
                p->setPen(QColor(14, 15, 18));
                
                int displayWidth = boundingRect().width();
                int displayHeight = boundingRect().height();
                
                double windowLeft = m_lower;
                double windowRight = m_upper;
                
                double step = (windowRight - windowLeft) / double(displayWidth);
                
                double pos = windowLeft;
                
                for(int x = 0; x < displayWidth; x++)
                {
                    double left = pos;
                    double right = pos + step;
                    
                    float height = m_histogram->GetRelativeBin(left, right);
                    
                    if(height >= 0)
                    {
                        p->drawLine(x, displayHeight * (1 - height), x, displayHeight);
                    }
                    
                    pos += step;
                }
                
                QPen pen;
                pen.setColor(QColor(158, 158, 158, 11));
                pen.setWidth(0.5);
                p->setPen(pen);
                
                const int gridSize = 5;
                
                qreal left = int(boundingRect().left()) - (int(boundingRect().left()) % gridSize);
                qreal top = int(boundingRect().top()) - (int(boundingRect().top()) % gridSize);
                
                QVarLengthArray<QLineF, 100> lines;
                
                for(qreal x = left; x < boundingRect().right(); x += gridSize)
                {
                    lines.append(QLineF(x, boundingRect().top(), x, boundingRect().bottom()));
                }
                
                for(qreal y = top; y < boundingRect().bottom(); y += gridSize)
                {
                    lines.append(QLineF(boundingRect().left(), y, boundingRect().right(), y));
                }
                
                p->drawLines(lines.data(), lines.size());
                
                p->restore();
            }
        }
        
        auto TransferFunctionCanvas::keyPressEvent(QKeyEvent* e) -> void
        {
            if(m_grabbedHandle == -1)
            {
                return;
            }
            
            switch(e->key())
            {
                case Qt::Key_Backspace:
                    if(this->getFunctionSize() > 1)
                    {
                        this->removeFunctionPoint(getFunctionX(m_grabbedHandle));
                        m_grabbedHandle = -1;
                    }
                    break;

                case Qt::Key_Left:
                    this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(getFunctionX(m_grabbedHandle) - 1, getFunctionY(m_grabbedHandle))));
                    break;

                case Qt::Key_Right:
                    this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(getFunctionX(m_grabbedHandle) + 1, getFunctionY(m_grabbedHandle))));
                    break;

                case Qt::Key_Up:
                    this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(getFunctionX(m_grabbedHandle), getFunctionY(m_grabbedHandle) + 0.001)));
                    break;

                case Qt::Key_Down:
                    this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(getFunctionX(m_grabbedHandle), getFunctionY(m_grabbedHandle) - 0.001)));
                    break;
                default:
                    break;
            }
            
            update();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto TransferFunctionCanvas::setImmediateUpdate(bool state) -> void
        {
            m_immediateUpdate = state;
        }
        
        auto TransferFunctionCanvas::getHistogram() -> mitk::SimpleHistogram*
        {
            return m_histogram;
        }
        
        auto TransferFunctionCanvas::setHistogram(mitk::SimpleHistogram* histogram) -> void
        {
            m_histogram = histogram;
        }
        
        auto TransferFunctionCanvas::getMin() -> double
        {
            return m_min;
        }
        
        auto TransferFunctionCanvas::setMin(double min) -> void
        {
            this->m_min = min;
            setLower(min);
        }
        
        auto TransferFunctionCanvas::getMax() -> double
        {
            return m_max;
        }
        
        auto TransferFunctionCanvas::setMax(double max) -> void
        {
            this->m_max = max;
            setUpper(max);
        }
        
        auto TransferFunctionCanvas::getLower() -> double
        {
            return m_lower;
        }
        
        auto TransferFunctionCanvas::setLower(double lower) -> void
        {
            this->m_lower = lower;
        }
        
        auto TransferFunctionCanvas::getUpper() -> double
        {
            return m_upper;
        }
        
        auto TransferFunctionCanvas::setUpper(double upper) -> void
        {
            this->m_upper = upper;
        }
        
        auto TransferFunctionCanvas::validateCoord(std::pair<double, double> x) -> std::pair<double, double>
        {
            double max = m_histogram->GetMax();
            double min = m_histogram->GetMin();
            
            if(x.first < min)
            {
                x.first = min;
            }
            if(x.first > max)
            {
                x.first = max;
            }
            if(x.second < 0)
            {
                x.second = 0;
            }
            if(x.second > 1)
            {
                x.second = 1;
            }

            return x;
        }
        
        auto TransferFunctionCanvas::setX(float x) -> void
        {
            if(m_grabbedHandle != -1)
            {
                this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(x, getFunctionY(m_grabbedHandle))));
                
                update();
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
        }
        
        auto TransferFunctionCanvas::setY(float y) -> void
        {
            if(m_grabbedHandle != -1)
            {
                this->moveFunctionPoint(m_grabbedHandle, validateCoord(std::make_pair(getFunctionX(m_grabbedHandle), y)));
                
                update();
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
        }
        
    }
}

