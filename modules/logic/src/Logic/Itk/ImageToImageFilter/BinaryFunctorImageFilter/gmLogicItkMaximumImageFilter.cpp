#include "gmLogicItkMaximumImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MaximumImageFilter::Register =
            Logic::Register<MaximumImageFilter>("itk",
                                                "MaximumImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1MaximumImageFilter.html");
        }
    }
}
