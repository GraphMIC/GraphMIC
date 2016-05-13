#include "gmImageStatisticsCalculationThread.hpp"

namespace gm
{
    namespace ViewItem
    {
        ImageStatisticsCalculation::ImageStatisticsCalculation():
        m_statisticsImage(nullptr),
        m_binaryMask(nullptr),
        m_planarFigureMask(nullptr),
        m_timeStep(0),
        m_IgnoreZeros(false),
        m_calculationSuccessful(false),
        m_statisticChanged(false),
        m_histogramBinSize(1.0),
        m_useDefaultBinSize(true)
        {
        }

        ImageStatisticsCalculation::~ImageStatisticsCalculation()
        {
        }

        auto ImageStatisticsCalculation::initialize(mitk::Image::Pointer image, mitk::Image::Pointer binaryImage, mitk::PlanarFigure::Pointer planarFig) -> void
        {
            if( this->m_statisticsImage.IsNotNull() )
                this->m_statisticsImage = nullptr;

            if( this->m_binaryMask.IsNotNull() )
                this->m_binaryMask = nullptr;

            if( this->m_planarFigureMask.IsNotNull())
                this->m_planarFigureMask = nullptr;

            if(image.IsNotNull())
                this->m_statisticsImage = image->Clone();
            if(binaryImage.IsNotNull())
                this->m_binaryMask = binaryImage->Clone();
            if(planarFig.IsNotNull())
                this->m_planarFigureMask = planarFig->Clone();
        }

        auto ImageStatisticsCalculation::setUseDefaultBinSize(bool useDefault) -> void
        {
            m_useDefaultBinSize = useDefault;
        }

        auto ImageStatisticsCalculation::setTimeStep(int times) -> void
        {
            this->m_timeStep = times;
        }

        auto ImageStatisticsCalculation::getTimeStep() -> int
        {
            return this->m_timeStep;
        }

        auto ImageStatisticsCalculation::getStatisticsData() -> std::vector<mitk::ImageStatisticsCalculator::Statistics>
        {
            return this->m_statisticsVector;
        }

        auto ImageStatisticsCalculation::getStatisticsImage() -> mitk::Image::Pointer
        {
            return this->m_statisticsImage;
        }

        auto ImageStatisticsCalculation::setIgnoreZeroValueVoxel(bool _arg) -> void
        {
            this->m_IgnoreZeros = _arg;
        }

        auto ImageStatisticsCalculation::getIgnoreZeroValueVoxel() -> bool
        {
            return this->m_IgnoreZeros;
        }

        auto ImageStatisticsCalculation::setHistogramBinSize(double size) -> void
        {
            this->m_histogramBinSize = size;
        }

        auto ImageStatisticsCalculation::getHistogramBinSize() -> double
        {
            return this->m_histogramBinSize;
        }

        auto ImageStatisticsCalculation::getTimeStepHistogram(unsigned int t) -> ImageStatisticsCalculation::HistogramType::Pointer
        {
            if (t >= this->m_histogramVector.size())
                return nullptr;

            return this->m_histogramVector[t];
        }

        auto ImageStatisticsCalculation::getStatisticsChangedFlag() -> bool
        {
            return m_statisticChanged;
        }

        auto ImageStatisticsCalculation::getStatisticsUpdateSuccessFlag() -> bool
        {
            return m_calculationSuccessful;
        }

        auto ImageStatisticsCalculation::run() -> void
        {
            bool statisticCalculationSuccessful = true;

            mitk::ImageStatisticsCalculator::Pointer calculator = mitk::ImageStatisticsCalculator::New();

            if(this->m_statisticsImage.IsNotNull())
            {
                calculator->SetImage(m_statisticsImage);
                calculator->SetMaskingModeToNone();
            }
            else
            {
                statisticCalculationSuccessful = false;
                return;
            }

            try
            {
                if(this->m_binaryMask.IsNotNull())
                {
                    calculator->SetImageMask(m_binaryMask);
                    calculator->SetMaskingModeToImage();
                }
                if(this->m_planarFigureMask.IsNotNull())
                {
                    calculator->SetPlanarFigure(m_planarFigureMask);
                    calculator->SetMaskingModeToPlanarFigure();
                }
            }
            catch( const itk::ExceptionObject& e)
            {
                statisticCalculationSuccessful = false;
            }

            bool statisticChanged = false;

            calculator->SetDoIgnorePixelValue(this->m_IgnoreZeros);
            calculator->SetIgnorePixelValue(0);
            calculator->SetHistogramBinSize(m_histogramBinSize);
            calculator->SetUseDefaultBinSize(m_useDefaultBinSize);

            if(!m_statisticsImage)
            {
                return;
            }

            for (unsigned int i = 0; i < m_statisticsImage->GetTimeSteps(); i++)
            {
                try
                {
                    statisticChanged = calculator->ComputeStatistics(i);
                }
                catch ( mitk::Exception& e)
                {
                    statisticCalculationSuccessful = false;
                }
                catch ( const std::runtime_error &e )
                {
                    statisticCalculationSuccessful = false;
                }
                catch ( const std::exception &e )
                {
                    statisticCalculationSuccessful = false;
                }
                catch (...)
                {
                    statisticCalculationSuccessful = false;
                }
            }

            this->m_statisticChanged = statisticChanged;
            this->m_calculationSuccessful = statisticCalculationSuccessful;

            if(statisticCalculationSuccessful)
            {
                this->m_statisticsVector.clear();
                this->m_histogramVector.clear();

                for (unsigned int i = 0; i < m_statisticsImage->GetTimeSteps(); i++)
                {
                    this->m_statisticsVector.push_back(calculator->GetStatistics(i));
                    this->m_histogramVector.push_back((HistogramType*)calculator->GetHistogram(i));
                }
            }

            m_histogramBinSize = calculator->GetHistogramBinSize();
        }
    }
}
