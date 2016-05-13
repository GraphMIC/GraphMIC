#include "gmLogicItkAndImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AndImageFilter::Register =
            Logic::Register<AndImageFilter>("itk",
                                            "AndImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1AndImageFilter.html");
        }
    }
}
