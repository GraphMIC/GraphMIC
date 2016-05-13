#include "gmLogicItkOrImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto OrImageFilter::Register =
            Logic::Register<OrImageFilter>("itk",
                                           "OrImageFilter",
                                           "http://www.itk.org/Doxygen/html/classitk_1_1OrImageFilter.html");
        }
    }
}
