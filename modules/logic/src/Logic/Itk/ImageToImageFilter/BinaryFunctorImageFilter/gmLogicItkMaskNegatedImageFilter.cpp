#include "gmLogicItkMaskNegatedImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MaskNegatedImageFilter::Register =
            Logic::Register<MaskNegatedImageFilter>("itk",
                                                    "MaskNegatedImageFilter",
                                                    "http://www.itk.org/Doxygen43/html/classitk_1_1MaskNegatedImageFilter.html");
        }
    }
}
