#include "gmLogicItkBilateralImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BilateralImageFilter::Register =
            Logic::Register<BilateralImageFilter>("itk",
                                                  "BilateralImageFilter",
                                                  "http://www.itk.org/Doxygen/html/classitk_1_1BilateralImageFilter.html");
        }
    }
}
