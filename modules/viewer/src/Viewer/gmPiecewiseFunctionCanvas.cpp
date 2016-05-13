#include "gmPiecewiseFunctionCanvas.hpp"
#include <QPainter>

namespace gm
{
    namespace ViewItem
    {
        PiecewiseFunctionCanvas* PiecewiseFunctionCanvas::instance = nullptr;
        
        PiecewiseFunctionCanvas::PiecewiseFunctionCanvas(QQuickPaintedItem* parent) :
        TransferFunctionCanvas(parent),
        m_piecewiseFunction(nullptr)
        {
            if(instance)
            {
                throw ("Instance already existing");
            }

            instance = this;
            setAcceptedMouseButtons(Qt::AllButtons);
            setAntialiasing(true);
        }
        
        PiecewiseFunctionCanvas::~PiecewiseFunctionCanvas()
        {
            
        }
        
        auto PiecewiseFunctionCanvas::setGreyValue(double value) -> void
        {
            this->m_greyValue = value;
            this->setX(value);
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto PiecewiseFunctionCanvas::getGreyValue() -> double
        {
            return this->m_greyValue;
        }
        
        auto PiecewiseFunctionCanvas::setOpacity(double opacity) -> void
        {
            this->m_opacity = opacity;
            this->setY(opacity);
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto PiecewiseFunctionCanvas::getOpacity() -> double
        {
            return this->m_opacity;
        }
        
        auto PiecewiseFunctionCanvas::setTitle(const QString &title) -> void
        {
            m_title = title;
        }
        
        auto PiecewiseFunctionCanvas::paint(QPainter* painter) -> void
        {
            paintHistogram(painter);
            
            if(m_title.size() > 0)
            {
                painter->setPen(Qt::black);
                painter->drawText(QPoint(11, 21), m_title);
                painter->setPen(Qt::white);
                painter->drawText(QPoint(10, 20), m_title);
            }
            
            painter->setPen(QColor(157, 166, 179));

            if(m_piecewiseFunction && this->isEnabled())
            {
                double* dp = m_piecewiseFunction->GetDataPointer();

                for(int i = -1; i < m_piecewiseFunction->GetSize(); i++)
                {
                    std::pair<int, int> left;
                    std::pair<int, int> right;
                    
                    if(i < 0)
                    {
                        left = this->functionToCanvas(std::make_pair(-32768, dp[0 * 2 + 1]));
                    }
                    else
                    {
                        left = this->functionToCanvas(std::make_pair(dp[i * 2], dp[i * 2 + 1]));
                    }
                    
                    if(i + 1 >= m_piecewiseFunction->GetSize())
                    {
                        right = this->functionToCanvas(std::make_pair(32768, dp[(i) * 2 + 1]));
                    }
                    else
                    {
                        right = this->functionToCanvas(std::make_pair(dp[(i + 1) * 2], dp[(i + 1) * 2 + 1]));
                    }
                    
                    painter->drawLine(left.first, left.second, right.first, right.second);
                }

                painter->setPen(QColor(40, 40, 40));
                
                for(int i = 0; i < m_piecewiseFunction->GetSize(); i++)
                {
                    std::pair<int, int> point = this->functionToCanvas(std::make_pair(dp[i * 2], dp[i * 2 + 1]));
                    
                    if(i == m_grabbedHandle)
                    {
                        painter->setBrush(QBrush(QColor(96, 177, 238)));
                        
                        this->m_opacity = QString::number(getFunctionY(m_grabbedHandle), 'g', 4).toFloat();
                        this->m_greyValue = QString::number(getFunctionX(m_grabbedHandle), 'g', 4).toFloat();
                        
                        emit this->sync();
                    }
                    else
                    {
                        painter->setBrush(QBrush(QColor(86, 86, 86)));
                    }

                    painter->drawEllipse(point.first - 4, point.second - 4, 8, 8);
                }
                
                painter->setBrush(Qt::NoBrush);
            }
        }
        
        int PiecewiseFunctionCanvas::getNearHandle(int x, int y, unsigned int maxSquaredDistance)
        {
            double* dp = m_piecewiseFunction->GetDataPointer();
            for(int i = 0; i < m_piecewiseFunction->GetSize(); i++)
            {
                std::pair<int, int> point = this->functionToCanvas(std::make_pair(dp[i * 2], dp[i * 2 + 1]));
                if((unsigned int) ((point.first - x) * (point.first - x) + (point.second - y) * (point.second - y)) <= maxSquaredDistance)
                {
                    return i;
                }
            }
            return -1;
        }
        
        void PiecewiseFunctionCanvas::moveFunctionPoint(int index, std::pair<double, double> pos)
        {
            removeFunctionPoint(getFunctionX(index));
            m_grabbedHandle = addFunctionPoint(pos.first, pos.second);
        }
        
        void PiecewiseFunctionCanvas::mousePressEvent(QMouseEvent* mouseEvent)
        {
            forceActiveFocus();
            TransferFunctionCanvas::mousePressEvent(mouseEvent);
        }
        
        void PiecewiseFunctionCanvas::mouseMoveEvent(QMouseEvent* mouseEvent)
        {
            TransferFunctionCanvas::mouseMoveEvent(mouseEvent);
        }
        
        void PiecewiseFunctionCanvas::mouseReleaseEvent(QMouseEvent* mouseEvent)
        {
            TransferFunctionCanvas::mouseReleaseEvent(mouseEvent);
        }
        
        void PiecewiseFunctionCanvas::mouseDoubleClickEvent(QMouseEvent* mouseEvent)
        {
            TransferFunctionCanvas::mouseDoubleClickEvent(mouseEvent);
        }
        
        void PiecewiseFunctionCanvas::keyPressEvent(QKeyEvent* keyEvent)
        {
            TransferFunctionCanvas::keyPressEvent(keyEvent);
        }
        
        void PiecewiseFunctionCanvas::setPiecewiseFunction(vtkPiecewiseFunction* piecewiseFunction)
        {
            this->m_piecewiseFunction = piecewiseFunction;
            this->setMin(m_piecewiseFunction->GetRange()[0]);
            this->setMax(m_piecewiseFunction->GetRange()[1]);
            setEnabled(true);
            
            update();
        }
        
        auto PiecewiseFunctionCanvas::addFunctionPoint(double x, double val) -> int
        {
            return m_piecewiseFunction->AddPoint(x, val);
        }
        
        auto PiecewiseFunctionCanvas::removeFunctionPoint(double x) -> void
        {
            int old_size = getFunctionSize();
            m_piecewiseFunction->RemovePoint(x);
            if(getFunctionSize() + 1 != old_size)
            {
                std::cout << "old/new size" << old_size << "/" << getFunctionSize() << std::endl;
                std::cout << "called with x=" << x << std::endl;
            }
        }
        
        auto PiecewiseFunctionCanvas::getFunctionX(int index) -> double
        {
            return m_piecewiseFunction->GetDataPointer()[index * 2];
        }
        
        auto PiecewiseFunctionCanvas::getFunctionY(int index) -> double
        {
            return m_piecewiseFunction->GetValue(m_piecewiseFunction->GetDataPointer()[index * 2]);
        }
        
        auto PiecewiseFunctionCanvas::getFunctionSize() -> int
        {
            return m_piecewiseFunction->GetSize();
        }
        
        void PiecewiseFunctionCanvas::doubleClickOnHandle(int)
        {
        }
        
        double PiecewiseFunctionCanvas::getFunctionMax()
        {
            return m_piecewiseFunction->GetRange()[1];
        }
        
        double PiecewiseFunctionCanvas::getFunctionMin()
        {
            return m_piecewiseFunction->GetRange()[0];
        }
        
        double PiecewiseFunctionCanvas::getFunctionRange()
        {
            double range;
            if((m_piecewiseFunction->GetRange()[0]) < 0)
            {
                range = (m_piecewiseFunction->GetRange()[1]) - (m_piecewiseFunction->GetRange()[0]);
                return range;
            }
            else
            {
                range = m_piecewiseFunction->GetRange()[1];
                return range;
            }
        }
        
        void PiecewiseFunctionCanvas::removeAllFunctionPoints()
        {
            m_piecewiseFunction->AddSegment(this->getFunctionMin(), 0, this->getFunctionMax(), 1);
            m_piecewiseFunction->AddPoint(0.0, 0.0);
        }
        
        void PiecewiseFunctionCanvas::resetGO()
        {
            m_piecewiseFunction->AddSegment(this->getFunctionMin(), 0, 0, 1);
            m_piecewiseFunction->AddSegment(0, 1, ((this->getFunctionRange()) * 0.125), 1);
            m_piecewiseFunction->AddSegment(((this->getFunctionRange()) * 0.125), 1, ((this->getFunctionRange()) * 0.2), 1);
            m_piecewiseFunction->AddSegment(((this->getFunctionRange()) * 0.2), 1, ((this->getFunctionRange()) * 0.25), 1);
        }
    }
}