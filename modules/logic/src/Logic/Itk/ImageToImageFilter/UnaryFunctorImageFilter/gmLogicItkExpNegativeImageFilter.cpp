#include "gmLogicItkExpNegativeImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ExpNegativeImageFilter::Register =
            Logic::Register<ExpNegativeImageFilter>("itk",
                                                    "ExpNegativeImageFilter",
                                                    "http://www.itk.org/Doxygen/html/classitk_1_1ExpNegativeImageFilter.html");
        }
    }
}
