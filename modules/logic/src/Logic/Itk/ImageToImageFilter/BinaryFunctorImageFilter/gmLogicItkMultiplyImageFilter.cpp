#include "gmLogicItkMultiplyImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MultiplyImageFilter::Register =
            Logic::Register<MultiplyImageFilter>("itk",
                                                 "MultiplyImageFilter",
                                                 "http://www.itk.org/Doxygen/html/classitk_1_1MultiplyImageFilter.html");
        }
    }
}
