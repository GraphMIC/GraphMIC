#include "gmLogicItkClampImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ClampImageFilter::Register =
            Logic::Register<ClampImageFilter>("itk",
                                              "ClampImageFilter",
                                              "http://www.itk.org/Doxygen/html/classitk_1_1ClampImageFilter.html");
        }
    }
}
