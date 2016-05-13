#include "gmLogicItkRGBToLuminanceImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto RGBToLuminanceImageFilter::Register =
            Logic::Register<RGBToLuminanceImageFilter>("itk",
                                                       "RGBToLuminanceImageFilter",
                                                       "http://www.itk.org/Doxygen/html/classitk_1_1RGBToLuminanceImageFilter.html");
        }
    }
}
