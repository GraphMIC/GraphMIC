#include "gmColorTransferFunctionCanvas.hpp"

#include <QPainter>
#include <QColorDialog>

namespace gm
{
    namespace ViewItem
    {
        ColorTransferFunctionCanvas::ColorTransferFunctionCanvas(QQuickPaintedItem* parent):
        TransferFunctionCanvas(parent), m_ColorTransferFunction(nullptr)
        {
        }
        
        ColorTransferFunctionCanvas::~ColorTransferFunctionCanvas()
        {
        }
        
        auto ColorTransferFunctionCanvas::setTitle(const QString &title) -> void
        {
            m_Title = title;
        }
        
        auto ColorTransferFunctionCanvas::setGreyValue(double value) -> void
        {
            this->m_GreyValue = value;
            this->setX(value);
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }
        
        auto ColorTransferFunctionCanvas::getGreyValue() -> double
        {
            return this->m_GreyValue;
        }
        
        auto ColorTransferFunctionCanvas::paint(QPainter* painter) -> void
        {
            QRectF contentsRect = this->boundingRect();
            painter->setPen(Qt::gray);
            
            if (m_ColorTransferFunction)
            {
                for (int x = (int) contentsRect.x(); x < contentsRect.x() + contentsRect.width(); x++)
                {
                    double xVal = m_min + ((float) x) / contentsRect.width() * (m_max - m_min);
                    QColor col((int) (m_ColorTransferFunction->GetRedValue(xVal) * 255),
                               (int) (m_ColorTransferFunction->GetGreenValue(xVal) * 255),
                               (int) (m_ColorTransferFunction->GetBlueValue(xVal) * 255));
                    painter->setPen(col);
                    painter->drawLine(x, 5, x, (int) contentsRect.height());
                }
            }

            if (m_Title.size()>0)
            {
                painter->setPen(Qt::black);
                painter->drawText(QPoint(11,21),m_Title);
                painter->setPen(Qt::white);
                painter->drawText(QPoint(10,20),m_Title);
            }

            if (m_ColorTransferFunction && this->isEnabled())
            {
                painter->setBrush(QColor(86, 86, 86));
                painter->setPen(QColor(40, 40, 40));

                for (int i = 0; i < this->getFunctionSize(); i++)
                {
                    int handleHeight    = (int) contentsRect.height();
                    int handleWidth     = 7;
                    std::pair<int,int> point = this->functionToCanvas(std::make_pair(getFunctionX(i), 0.0f));
                    int y = (int) (height() / 2);
                    
                    QRectF rect = QRectF(point.first - handleWidth / 2, y - handleHeight / 2, handleWidth, handleHeight);
                    QPainterPath path;
                    path.moveTo(rect.left() + (rect.width() / 2), rect.top());
                    path.lineTo(rect.left(), rect.top()+rect.height()/3);
                    path.lineTo(rect.bottomLeft());
                    path.lineTo(rect.bottomRight());
                    path.lineTo(rect.right(), rect.top()+rect.height()/3);
                    path.lineTo(rect.left() + (rect.width() / 2), rect.top());
                    
                    QColor color(86, 86, 86);

                    if(i == m_grabbedHandle)
                        color.setRgb(96, 177, 238);

                    painter->setBrush(color);
                    painter->setPen(QColor(40, 40, 40));
                    painter->drawPath(path);

                    if (i == m_grabbedHandle)
                    {
                        this->m_GreyValue = QString::number(getFunctionX(m_grabbedHandle), 'g', 4).toFloat();
                        emit this->sync();
                    }
                }
            }
        }
        
        auto ColorTransferFunctionCanvas::getNearHandle(int x, int, unsigned int maxSquaredDistance) -> int
        {
            for (int i = 0; i < this->getFunctionSize(); i++)
            {
                std::pair<int,int> point = this->functionToCanvas(std::make_pair(
                                                                                 getFunctionX(i), (double) 0.0));
                if ((unsigned int) ((point.first - x) * (point.first - x))
                    < maxSquaredDistance)
                {
                    return i;
                }
            }
            return -1;
        }
        
        auto ColorTransferFunctionCanvas::doubleClickOnHandle(int handle) -> void
        {
            double xVal = getFunctionX(handle);
            QColor col((int) (m_ColorTransferFunction->GetRedValue(xVal) * 255),
                       (int) (m_ColorTransferFunction->GetGreenValue(xVal) * 255),
                       (int) (m_ColorTransferFunction->GetBlueValue(xVal) * 255));
            QColor result = QColorDialog::getColor(col);
            if (result.isValid())
            {
                m_ColorTransferFunction->AddRGBPoint(xVal, result.red() / 255.0,
                                                     result.green() / 255.0, result.blue() / 255.0);
                this->update();
                mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
            }
        }
        
        auto ColorTransferFunctionCanvas::moveFunctionPoint(int index, std::pair<double,double> pos) -> void
        {
            double color[3];
            m_ColorTransferFunction->GetColor(getFunctionX(index), color);
            removeFunctionPoint( getFunctionX(index));
            m_ColorTransferFunction->AddRGBPoint(pos.first, color[0], color[1], color[2]);
        }
        
        auto ColorTransferFunctionCanvas::addRGB(double x, double r, double g, double b) -> void
        {
            m_ColorTransferFunction->AddRGBPoint(x, r, g, b);
        }
        
        auto ColorTransferFunctionCanvas::getFunctionMax() -> double
        {
            return m_ColorTransferFunction->GetRange()[1];
        }
        
        auto ColorTransferFunctionCanvas::getFunctionMin() -> double
        {
            return m_ColorTransferFunction->GetRange()[0];
        }
        
        auto ColorTransferFunctionCanvas::getFunctionRange() -> double
        {
            double range;

            if((m_ColorTransferFunction->GetRange()[0])==0)
            {
                range = m_ColorTransferFunction->GetRange()[1];
                return range;
            }
            else
            {
                range = (m_ColorTransferFunction->GetRange()[1])-(m_ColorTransferFunction->GetRange()[0]);
                return range;
            }
        }
        
        auto ColorTransferFunctionCanvas::removeAllFunctionPoints() -> void
        {
            m_ColorTransferFunction->AddRGBSegment(this->getFunctionSize(),1,0,0,this->getFunctionMax(),1,1,0);
        }
        
        auto ColorTransferFunctionCanvas::getFunctionY(int) -> double
        {
            return 0.0;
        }
        
        auto ColorTransferFunctionCanvas::setColorTransferFunction(vtkColorTransferFunction* colorTransferFunction) -> void
        {
            this->m_ColorTransferFunction = colorTransferFunction;
            this->setMin(colorTransferFunction->GetRange()[0]);
            this->setMax(colorTransferFunction->GetRange()[1]);
            setEnabled(true);
            update();
        }
        
        auto ColorTransferFunctionCanvas::addFunctionPoint(double x, double) -> int
        {
            return m_ColorTransferFunction->AddRGBPoint(x,m_ColorTransferFunction->GetRedValue(x),m_ColorTransferFunction->GetGreenValue(x),m_ColorTransferFunction->GetBlueValue(x));
        }
        
        auto ColorTransferFunctionCanvas::removeFunctionPoint(double x) -> void
        {
            m_ColorTransferFunction->RemovePoint(x);
        }
        
        auto ColorTransferFunctionCanvas::getFunctionX(int index) -> double
        {
            return m_ColorTransferFunction->GetDataPointer()[index*4];
        }
        
        auto ColorTransferFunctionCanvas::getFunctionSize() -> int
        {
            return m_ColorTransferFunction->GetSize();
        }
    }
}
