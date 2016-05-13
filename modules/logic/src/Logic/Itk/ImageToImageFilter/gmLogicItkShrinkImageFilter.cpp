#include "gmLogicItkShrinkImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ShrinkImageFilter::Register =
            Logic::Register<ShrinkImageFilter>("itk",
                                               "ShrinkImageFilter",
                                               "http://www.itk.org/Doxygen/html/classitk_1_1ShrinkImageFilter.html");
        }
    }
}
