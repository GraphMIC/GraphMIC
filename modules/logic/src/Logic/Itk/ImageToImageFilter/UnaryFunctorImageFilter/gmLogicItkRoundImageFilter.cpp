#include "gmLogicItkRoundImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto RoundImageFilter::Register =
            Logic::Register<RoundImageFilter>("itk",
                                              "RoundImageFilter",
                                              "http://www.itk.org/Doxygen/html/classitk_1_1RoundImageFilter.html");
        }
    }
}
