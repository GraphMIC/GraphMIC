#include "gmLogicItkAbsoluteValueDifferenceImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AbsoluteValueDifferenceImageFilter::Register =
            Logic::Register<AbsoluteValueDifferenceImageFilter>("itk",
                                                                "AbsoluteValueDifferenceImageFilter",
                                                                "http://www.itk.org/Doxygen/html/classitk_1_1AbsoluteValueDifferenceImageFilter.html");
        }
    }
}
