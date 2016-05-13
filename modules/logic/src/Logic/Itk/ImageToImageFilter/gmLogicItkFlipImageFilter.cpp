#include "gmLogicItkFlipImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto FlipImageFilter::Register =
            Logic::Register<FlipImageFilter>("itk",
                                             "FlipImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1FlipImageFilter.html");
        }
    }
}
