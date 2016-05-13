#include "gmLogicItkDivideImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto DivideImageFilter::Register =
            Logic::Register<DivideImageFilter>("itk",
                                               "DivideImageFilter",
                                               "http://www.itk.org/Doxygen/html/classitk_1_1DivideImageFilter.html");
        }
    }
}
