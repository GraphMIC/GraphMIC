#include "gmLogicItkAsinImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AsinImageFilter::Register =
            Logic::Register<AsinImageFilter>("itk",
                                             "AsinImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1AsinImageFilter.html");
        }
    }
}
