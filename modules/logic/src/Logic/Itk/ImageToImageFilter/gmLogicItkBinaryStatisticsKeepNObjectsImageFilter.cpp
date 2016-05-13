#include "gmLogicItkBinaryStatisticsKeepNObjectsImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryStatisticsKeepNObjectsImageFilter::Register =
            Logic::Register<BinaryStatisticsKeepNObjectsImageFilter>("itk",
                                                                     "BinaryStatisticsKeepNObjectsImageFilter",
                                                                     "http://www.itk.org/Doxygen/html/classitk_1_1BinaryStatisticsKeepNObjectsImageFilter.html");
        }
    }
}
