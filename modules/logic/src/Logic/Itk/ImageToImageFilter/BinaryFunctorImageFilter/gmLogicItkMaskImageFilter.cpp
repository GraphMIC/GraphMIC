#include "gmLogicItkMaskImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MaskImageFilter::Register =
            Logic::Register<MaskImageFilter>("itk",
                                             "MaskImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1MaskImageFilter.html");
        }
    }
}
