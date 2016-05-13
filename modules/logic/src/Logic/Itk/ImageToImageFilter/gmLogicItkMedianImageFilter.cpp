#include "gmLogicItkMedianImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MedianImageFilter::Register =
            Logic::Register<MedianImageFilter>("itk",
                                               "MedianImageFilter",
                                               "http://www.itk.org/Doxygen/html/classitk_1_1MedianImageFilter.html");
        }
    }
}
