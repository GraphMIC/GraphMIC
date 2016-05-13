#pragma once

#include "gmViewerExport.hpp"

#include "mitkImage.h"
#include "mitkPlanarFigure.h"
#include "mitkImageStatisticsCalculator.h"

#include <itkPolyLineParametricPath.h>
#include <QQuickPaintedItem>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT HistogramItem: public QQuickPaintedItem
        {
            Q_OBJECT
            Q_PROPERTY(int min READ getMin WRITE setMin NOTIFY minChanged);
            Q_PROPERTY(int max READ getMax WRITE setMax NOTIFY maxChanged);
            Q_PROPERTY(int currentMin READ getCurrentMin WRITE setCurrentMin NOTIFY currentMinChanged);
            Q_PROPERTY(int currentMax READ getCurrentMax WRITE setCurrentMax NOTIFY currentMaxChanged);
            Q_PROPERTY(QString binInfo READ getBinInfo WRITE setBinInfo NOTIFY binInfoChanged);
        private:
            int m_min;
            int m_max;
            int m_currentMin;
            int m_currentMax;
            double  m_maxMeas;
            QPoint  m_currentPos;
            QString      m_binInfo;
            QList<float> m_frequency;
            QList<float> m_currentFrequency;
            QList<float> m_measurement;
            QList<float> m_currentMeasurement;
            mitk::Image::Pointer m_image;
            mitk::ImageStatisticsCalculator::HistogramType::ConstPointer m_histogram;
        private:
            void clearData();
        public:
            typedef mitk::Image::HistogramType      HistogramType;
            typedef HistogramType::ConstIterator    HistogramConstIteratorType;
            explicit HistogramItem(QQuickPaintedItem *parent = nullptr);
            ~HistogramItem();
            auto setMin(int min) -> void;
            auto setMax(int max) -> void;
            auto setCurrentMin(int currentMin) -> void;
            auto setCurrentMax(int currentMax) -> void;
            auto setBinInfo(QString info) -> void;
            auto getBinInfo() -> QString;
            auto getMin() -> int;
            auto getMax() -> int;
            auto getCurrentMin() -> int;
            auto getCurrentMax() -> int;
            void paint(QPainter* painter) override;
            void geometryChanged(const QRectF &, const QRectF &) override;
            auto hoverMoveEvent(QHoverEvent *event) -> void override;
            auto hoverEnterEvent(QHoverEvent *even) -> void override;
            auto computeHistogram(HistogramType* histogram, double maxMeasure) -> void;
            auto clearHistogram() -> void;
            auto generateSteps(int freq) -> std::tuple<int, int>;
            auto trimLabel(int num) -> QString;
            auto getMeasurement() -> QList<float>;
            auto getFrequency() -> QList<float> ;
            auto setImage(mitk::Image* image) -> void;
        signals:
            void currentMinChanged();
            void currentMaxChanged();
            void minChanged();
            void maxChanged();
            void sync();
            void binInfoChanged();
        };
    }
}

