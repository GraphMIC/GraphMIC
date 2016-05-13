#include "gmLogicItkSquareImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SquareImageFilter::Register =
            Logic::Register<SquareImageFilter>("itk",
                                               "SquareImageFilter",
                                               "http://www.itk.org/Doxygen/html/classitk_1_1SquareImageFilter.html");
        }
    }
}
