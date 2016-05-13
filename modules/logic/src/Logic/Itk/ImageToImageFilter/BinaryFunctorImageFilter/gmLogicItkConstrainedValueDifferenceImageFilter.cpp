#include "gmLogicItkConstrainedValueDifferenceImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ConstrainedValueDifferenceImageFilter::Register =
            Logic::Register<ConstrainedValueDifferenceImageFilter>("itk",
                                                                   "ConstrainedValueDifferenceImageFilter",
                                                                   "http://www.itk.org/Doxygen/html/classitk_1_1ConstrainedValueDifferenceImageFilter.html");
        }
    }
}
