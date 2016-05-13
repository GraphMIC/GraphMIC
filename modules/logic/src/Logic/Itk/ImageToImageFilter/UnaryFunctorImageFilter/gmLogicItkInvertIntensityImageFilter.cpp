#include "gmLogicItkInvertIntensityImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto InvertIntensityImageFilter::Register =
            Logic::Register<InvertIntensityImageFilter>("itk",
                                                        "InvertIntensityImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1InvertIntensityImageFilter.html");
        }
    }
}
