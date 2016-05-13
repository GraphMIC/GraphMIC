#include "gmLogicItkNotImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto NotImageFilter::Register =
            Logic::Register<NotImageFilter>("itk",
                                            "NotImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1NotImageFilter.html");
        }
    }
}
