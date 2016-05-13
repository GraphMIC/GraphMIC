#include "gmLogicItkSinImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SinImageFilter::Register =
            Logic::Register<SinImageFilter>("itk",
                                            "SinImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1SinImageFilter.html");
        }
    }
}
