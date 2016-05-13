#include "gmLogicItkPowImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto PowImageFilter::Register =
            Logic::Register<PowImageFilter>("itk",
                                            "PowImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1PowImageFilter.html");
        }
    }
}
