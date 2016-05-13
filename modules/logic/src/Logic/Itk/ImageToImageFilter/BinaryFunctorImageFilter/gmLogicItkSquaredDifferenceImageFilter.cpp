#include "gmLogicItkSquaredDifferenceImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SquaredDifferenceImageFilter::Register =
            Logic::Register<SquaredDifferenceImageFilter>("itk",
                                                          "SquaredDifferenceImageFilter",
                                                          "http://www.itk.org/Doxygen/html/classitk_1_1SquaredDifferenceImageFilter.html");
        }
    }
}
