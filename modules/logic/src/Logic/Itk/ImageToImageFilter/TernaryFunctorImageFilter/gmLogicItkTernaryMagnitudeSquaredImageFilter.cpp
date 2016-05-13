#include "gmLogicItkTernaryMagnitudeSquaredImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto TernaryMagnitudeSquaredImageFilter::Register =
            Logic::Register<TernaryMagnitudeSquaredImageFilter>("itk",
                                                                "TernaryMagnitudeSquaredImageFilter",
                                                                "http://www.itk.org/Doxygen/html/classitk_1_1TernaryMagnitudeSquaredImageFilter.html");
        }
    }
}