#include "gmLogicItkLaplacianImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto LaplacianImageFilter::Register =
            Logic::Register<LaplacianImageFilter>("itk",
                                                  "LaplacianImageFilter",
                                                  "http://www.itk.org/Doxygen/html/classitk_1_1LaplacianImageFilter.html");
        }
    }
}
