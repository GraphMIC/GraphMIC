#include "gmLogicItkCastImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CastImageFilter::Register =
            Logic::Register<CastImageFilter>("itk",
                                             "CastImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1CastImageFilter.html");
        }
    }
}
