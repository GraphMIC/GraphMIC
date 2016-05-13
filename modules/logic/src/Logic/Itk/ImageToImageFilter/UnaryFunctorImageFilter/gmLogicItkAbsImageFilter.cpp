#include "gmLogicItkAbsImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AbsImageFilter::Register =
            Logic::Register<AbsImageFilter>("itk",
                                            "AbsImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1AbsImageFilter.html");
        }
    }
}
