#include "gmLogicItkBinaryStatisticsOpeningImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryStatisticsOpeningImageFilter::Register =
            Logic::Register<BinaryStatisticsOpeningImageFilter>("itk",
                                                                "BinaryStatisticsOpeningImageFilter",
                                                                "http://www.itk.org/Doxygen/html/classitk_1_1BinaryStatisticsOpeningImageFilter.html");
        }
    }
}
