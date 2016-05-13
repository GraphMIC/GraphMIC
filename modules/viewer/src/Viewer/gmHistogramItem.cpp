#include "gmHistogramItem.hpp"
#include <mitkImagePixelReadAccessor.h>
#include <mitkIntensityProfile.h>
#include <mitkRenderingManager.h>
#include <mitkBaseRenderer.h>
#include <mitkImageTimeSelector.h>
#include <mitkExtractSliceFilter.h>
#include <QPainter>
#include <QQuickWindow>

namespace gm
{
    namespace ViewItem
    {
        HistogramItem::HistogramItem(QQuickPaintedItem* parent):
        QQuickPaintedItem(parent),
        m_max(100),
        m_min(0),
        m_currentMin(0),
        m_currentMax(100)
        {
            setAcceptHoverEvents(true);
        }

        HistogramItem::~HistogramItem()
        {
        }

        auto HistogramItem::setBinInfo(QString info) -> void
        {
            this->m_binInfo = info;
            emit this->binInfoChanged();
        }

        auto HistogramItem::getBinInfo() -> QString
        {
            return this->m_binInfo;
        }

        auto HistogramItem::setMin(int min) -> void
        {
            this->m_min = min;
            emit this->minChanged();
        }

        auto HistogramItem::setMax(int max) -> void
        {
            this->m_max = max;
            emit this->maxChanged();
        }

        auto HistogramItem::setCurrentMin(int currentMin) -> void
        {
            this->m_currentMin = currentMin;
        }

        auto HistogramItem::setCurrentMax(int currentMax) -> void
        {
            this->m_currentMax = currentMax;
        }

        auto HistogramItem::getMin() -> int
        {
            return this->m_min;
        }

        auto HistogramItem::getMax() -> int
        {
            return this->m_max;
        }

        auto HistogramItem::getCurrentMin() -> int
        {

            return this->m_currentMin;
        }

        auto HistogramItem::getCurrentMax() -> int
        {
            return this->m_currentMax;
        }

        void HistogramItem::geometryChanged(const QRectF &, const QRectF &)
        {
            update();
        }

        auto HistogramItem::hoverMoveEvent(QHoverEvent* event) -> void
        {
            this->m_currentPos = event->pos();
            update();
        }

        auto HistogramItem::trimLabel(int num) -> QString
        {
            QString lab = QString::number(num);

            if(lab.size() > 6)
            {
                lab.chop(5);
                lab.append("m");
                lab.insert(lab.size() - 2, ".");
            }
            else if(lab.size() > 3)
            {
                lab.chop(3);
                lab.append("k");
            }

            return lab;
        }

        auto HistogramItem::generateSteps(int freq) -> std::tuple<int, int>
        {
            QString label = QString::number(freq);
            for(int i = 2; i < label.size(); i++)
            {
                label.replace(i, 1, "0");
            }

            int steps = label.left(2).toInt();
            int stepSize = label.toInt() / steps;

            while(steps > 20)
            {
                steps /= 2;
                stepSize *= 2;
            }

            return std::tuple<int, int>(steps, stepSize);
        }

        void HistogramItem::paint(QPainter* painter)
        {
            if(!m_histogram)
            {
                return;
            }

            int brushWidth = 1;
            int spacer = 35;
            int marker_size = 4;
            int margin = 4;

            int displayWidth = this->contentsBoundingRect().width();
            int displayHeight = this->contentsBoundingRect().height();

            QPen pen;
            pen.setWidth(brushWidth);
            pen.setBrush(QColor(157, 166, 179));
            painter->setPen(pen);

            painter->drawLine(spacer, displayHeight - spacer, displayWidth, displayHeight - spacer);
            painter->drawLine(spacer, 0, spacer, displayHeight - spacer);

            float max_freq = *std::max_element(m_currentFrequency.begin(), m_currentFrequency.end());
            float max_meas = m_maxMeas;

            float freqRatio = (displayHeight - spacer) / max_freq;
            float measRatio = (displayWidth - spacer) / max_meas;
            float barWidth = (displayWidth - spacer) / m_currentMeasurement.size();

            QFont font;
            font.setPixelSize(10);
            painter->setFont(font);

            std::tuple<int, int> freqLabels = this->generateSteps(max_freq);
            std::tuple<int, int> measLabels = this->generateSteps(max_meas);

            for(int i = 0; i <= std::get<0>(freqLabels); i++)
            {
                int freqNbr = std::get<1>(freqLabels) * i;
                int x = spacer - marker_size;
                int y = displayHeight - spacer - freqRatio * freqNbr;

                if(y > margin)
                {
                    painter->drawLine(x, y, spacer, y);
                }

                QString freq = trimLabel(freqNbr);
                QRect freqRect = painter->fontMetrics().boundingRect(freq);

                int x_point = spacer - 2 * marker_size - freqRect.width();
                int y_point = y + freqRect.height() / 2 - 2;

                if(y_point > margin)
                {
                    painter->drawText(QPoint(x_point, y_point), freq);
                }
            }

            painter->setBrush(QColor(14, 15, 18));

            for(int i = 0; i < m_currentMeasurement.size(); i++)
            {
                float h = m_currentFrequency.at(i) * freqRatio;
                int x = m_currentMeasurement.at(i) * measRatio;
                int y = displayHeight - spacer;

                if(i != 0)
                {
                    barWidth = (m_currentMeasurement.at(i) - m_currentMeasurement.at(i - 1)) * measRatio;
                }

                h = ceil(h);
                x = x + spacer - barWidth / 2 + brushWidth;

                painter->fillRect(x, y, round(barWidth), -h, QColor(14, 15, 18));

                int posX = this->m_currentPos.x();

                int intervall = x + barWidth;

                if(posX >= x && posX < intervall)
                {
                    //std::cout << "posX(" << posX << ") >= x(" << x << ") && posX(" << posX << ") <= intervall(" << intervall << ")" << std::endl;

                    float measRange;
                    QString info;

                    if(i == 0)
                    {
                        measRange = m_currentMeasurement.at(i);
                        info = QString("<b>GreyValue:</b> %1 .. %2 <br /><b>Frequency:</b> %3").arg(0).arg(2 * m_currentMeasurement.at(i)).arg(h / freqRatio);
                    }
                    else
                    {
                        measRange = m_currentMeasurement.at(i) - m_currentMeasurement.at(i - 1);
                        info = QString("<b>GreyValue:</b> %1 .. %2 <br /><b>Frequency:</b> %3").arg(m_currentMeasurement.at(i) - measRange / 2).arg(m_currentMeasurement.at(i) + measRange / 2).arg(h / freqRatio);
                    }

                    this->setBinInfo(info);

                    painter->fillRect(x, y, round(barWidth), -h, QColor(96, 177, 238));
                }
            }

            for(int i = 0; i <= std::get<0>(measLabels); i++)
            {
                int measNbr = std::get<1>(measLabels) * i;
                int x = measRatio * measNbr + spacer;
                int y = displayHeight - spacer;

                painter->drawLine(x, y, x, y + marker_size);
                painter->save();

                QString meas = trimLabel(measNbr);
                QRect measRect = painter->fontMetrics().boundingRect(meas);

                painter->translate(QPointF(x - measRect.width() / 2, y + marker_size + measRect.height()));
                painter->rotate(45);
                painter->drawText(0, 0, meas);
                painter->resetTransform();
                painter->restore();
            }
        }

        auto HistogramItem::hoverEnterEvent(QHoverEvent* /*event*/) -> void
        {
            forceActiveFocus();
        }

        void HistogramItem::computeHistogram(HistogramType* histogram, double maxMeasure)
        {
            m_histogram = histogram;
            m_maxMeas = maxMeasure;

            HistogramConstIteratorType startIt = m_histogram->End();
            HistogramConstIteratorType endIt = m_histogram->End();
            HistogramConstIteratorType it = m_histogram->Begin();
            clearData();
            unsigned int i = 0;
            bool firstValue = false;

            for(; it != m_histogram->End(); ++it)
            {
                if(it.GetFrequency() > 0.0)
                {
                    endIt = it;
                    if(!firstValue)
                    {
                        firstValue = true;
                        startIt = it;
                    }
                }
            }
            ++endIt;

            for(it = startIt; it != endIt; ++it, ++i)
            {
                float frequency = it.GetFrequency();
                float measurement = it.GetMeasurementVector()[0];
                m_frequency.insert(i, frequency);
                m_measurement.insert(i, measurement);
            }


            this->m_currentMeasurement = m_measurement;
            this->m_currentFrequency = m_frequency;

            this->setMin(0);
            this->setMax(m_measurement.size());
            this->setCurrentMin(0);
            this->setCurrentMax(m_measurement.size());
            emit this->sync();
            this->update();
        }

        void HistogramItem::clearData()
        {
            m_frequency.clear();
            m_measurement.clear();
        }

        void HistogramItem::clearHistogram()
        {
            this->clearData();
        }

        QList<float> HistogramItem::getFrequency()
        {
            return m_frequency;
        }

        QList<float> HistogramItem::getMeasurement()
        {
            return m_measurement;
        }

        void HistogramItem::setImage(mitk::Image* image)
        {
            m_image = image;
        }
    }
}

