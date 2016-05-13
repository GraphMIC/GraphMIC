#include "gmLogicItkSubtractImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SubtractImageFilter::Register =
            Logic::Register<SubtractImageFilter>("itk",
                                                 "SubtractImageFilter",
                                                 "http://www.itk.org/Doxygen/html/classitk_1_1SubtractImageFilter.html");
        }
    }
}
