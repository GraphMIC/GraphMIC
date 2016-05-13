#include "gmLogicItkTernaryMagnitudeImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto TernaryMagnitudeImageFilter::Register =
            Logic::Register<TernaryMagnitudeImageFilter>("itk",
                                                         "TernaryMagnitudeImageFilter",
                                                         "http://www.itk.org/Doxygen/html/classitk_1_1TernaryMagnitudeImageFilter.html");
        }
    }
}