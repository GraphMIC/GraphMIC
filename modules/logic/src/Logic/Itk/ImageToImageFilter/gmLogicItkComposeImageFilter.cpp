#include "gmLogicItkComposeImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ComposeImageFilter::Register =
            Logic::Register<ComposeImageFilter>("itk",
                                             "ComposeImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1ComposeImageFilter.html");
        }
    }
}
