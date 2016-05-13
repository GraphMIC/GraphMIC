#include "gmLogicItkRescaleIntensityImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto RescaleIntensityImageFilter::Register =
            Logic::Register<RescaleIntensityImageFilter>("itk",
                                                         "RescaleIntensityImageFilter",
                                                         "http://www.itk.org/Doxygen/html/classitk_1_1RescaleIntensityImageFilter.html");
        }
    }
}
