#include "gmLogicItkNaryMaximumImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto NaryMaximumImageFilter::Register =
            Logic::Register<NaryMaximumImageFilter>("itk",
                                                    "NaryMaximumImageFilter",
                                                    "http://www.itk.org/Doxygen/html/classitk_1_1NaryMaximumImageFilter.html");
        }
    }
}
