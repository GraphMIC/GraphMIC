#include "gmLogicItkMinimumImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MinimumImageFilter::Register =
            Logic::Register<MinimumImageFilter>("itk",
                                                "MinimumImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1MinimumImageFilter.html");
        }
    }
}
