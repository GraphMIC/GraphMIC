#include "gmLogicItkWeightedAddImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto WeightedAddImageFilter::Register =
            Logic::Register<WeightedAddImageFilter>("itk",
                                                    "WeightedAddImageFilter",
                                                    "http://www.itk.org/Doxygen/html/classitk_1_1WeightedAddImageFilter.html");
        }
    }
}
