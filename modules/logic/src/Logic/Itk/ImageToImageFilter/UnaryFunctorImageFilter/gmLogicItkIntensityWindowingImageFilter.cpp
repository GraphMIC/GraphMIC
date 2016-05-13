#include "gmLogicItkIntensityWindowingImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto IntensityWindowingImageFilter::Register =
            Logic::Register<IntensityWindowingImageFilter>("itk",
                                                           "IntensityWindowingImageFilter",
                                                           "http://www.itk.org/Doxygen/html/classitk_1_1IntensityWindowingImageFilter.html");
        }
    }
}
