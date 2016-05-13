#include "gmLogicItkAccumulateImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AccumulateImageFilter::Register =
            Logic::Register<AccumulateImageFilter>("itk",
                                                   "AccumulateImageFilter",
                                                   "http://www.itk.org/Doxygen/html/classitk_1_1AccumulateImageFilter.html");
        }
    }
}
