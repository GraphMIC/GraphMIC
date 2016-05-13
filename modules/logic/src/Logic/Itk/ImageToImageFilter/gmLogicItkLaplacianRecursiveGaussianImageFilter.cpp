#include "gmLogicItkLaplacianRecursiveGaussianImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto LaplacianRecursiveGaussianImageFilter::Register =
            Logic::Register<LaplacianRecursiveGaussianImageFilter>("itk",
                                                                   "LaplacianRecursiveGaussianImageFilter",
                                                                   "http://www.itk.org/Doxygen/html/classitk_1_1LaplacianRecursiveGaussianImageFilter.html");
        }
    }
}
