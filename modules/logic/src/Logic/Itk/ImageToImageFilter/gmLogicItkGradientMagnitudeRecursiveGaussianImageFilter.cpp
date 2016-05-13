#include "gmLogicItkGradientMagnitudeRecursiveGaussianImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto GradientMagnitudeRecursiveGaussianImageFilter::Register =
            Logic::Register<GradientMagnitudeRecursiveGaussianImageFilter>("itk",
                                                                           "GradientMagnitudeRecursiveGaussianImageFilter",
                                                                           "http://www.itk.org/Doxygen/html/classitk_1_1GradientMagnitudeRecursiveGaussianImageFilter.html");
        }
    }
}
