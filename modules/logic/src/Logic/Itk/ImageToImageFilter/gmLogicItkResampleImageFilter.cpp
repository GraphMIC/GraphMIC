#include "gmLogicItkResampleImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ResampleImageFilter::Register =
            Logic::Register<ResampleImageFilter>("itk",
                                                 "ResampleImageFilter",
                                                 "http://www.itk.org/Doxygen/html/classitk_1_1ResampleImageFilter.html");
        }
    }
}
