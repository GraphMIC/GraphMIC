#pragma once

#include "gmViewerExport.hpp"

#include <mitkImage.h>
#include <mitkPlanarFigure.h>
#include <mitkImageStatisticsCalculator.h>
#include <itkHistogram.h>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT ImageStatisticsCalculation
        {
        private:
            int         m_timeStep;
            bool        m_IgnoreZeros;
            bool        m_statisticChanged;
            bool        m_calculationSuccessful;
            bool        m_useDefaultBinSize;
            double      m_histogramBinSize;
            mitk::Image::Pointer        m_statisticsImage;
            mitk::Image::Pointer        m_binaryMask;
            mitk::PlanarFigure::Pointer m_planarFigureMask;
            std::vector<mitk::ImageStatisticsCalculator::Statistics> m_statisticsVector;
            std::vector<itk::Statistics::Histogram<double>::Pointer> m_histogramVector;
        public:
            typedef itk::Statistics::Histogram<double> HistogramType;
        public:
            ImageStatisticsCalculation();
            ~ImageStatisticsCalculation();
            auto setUseDefaultBinSize(bool useDefault) -> void;
            auto initialize(mitk::Image::Pointer image, mitk::Image::Pointer binaryImage, mitk::PlanarFigure::Pointer planarFig) -> void;
            auto getStatisticsData() -> std::vector<mitk::ImageStatisticsCalculator::Statistics>;
            auto getStatisticsImage() -> mitk::Image::Pointer;
            auto setTimeStep(int times) -> void;
            auto getTimeStep() -> int;
            auto setIgnoreZeroValueVoxel(bool _arg) -> void;
            auto getIgnoreZeroValueVoxel() -> bool;
            auto setHistogramBinSize(double size) -> void;
            auto getHistogramBinSize() -> double;
            auto getTimeStepHistogram(unsigned int t = 0) -> HistogramType::Pointer;
            auto getStatisticsChangedFlag() -> bool;
            auto getStatisticsUpdateSuccessFlag() -> bool;
            auto run() -> void;
        };
    }
}
