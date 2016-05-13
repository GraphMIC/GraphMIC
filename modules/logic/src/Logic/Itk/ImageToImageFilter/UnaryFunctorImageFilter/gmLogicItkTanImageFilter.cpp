#include "gmLogicItkTanImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto TanImageFilter::Register =
            Logic::Register<TanImageFilter>("itk",
                                            "TanImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1TanImageFilter.html");
        }
    }
}
