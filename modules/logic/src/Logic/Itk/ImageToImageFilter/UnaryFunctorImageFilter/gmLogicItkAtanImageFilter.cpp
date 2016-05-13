#include "gmLogicItkAtanImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AtanImageFilter::Register =
            Logic::Register<AtanImageFilter>("itk",
                                             "AtanImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1AtanImageFilter.html");
        }
    }
}
