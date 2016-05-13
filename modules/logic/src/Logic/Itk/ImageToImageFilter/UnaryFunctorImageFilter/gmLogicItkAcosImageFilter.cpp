#include "gmLogicItkAcosImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AcosImageFilter::Register =
            Logic::Register<AcosImageFilter>("itk",
                                             "AcosImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1CastImageFilter.html");
        }
    }
}
