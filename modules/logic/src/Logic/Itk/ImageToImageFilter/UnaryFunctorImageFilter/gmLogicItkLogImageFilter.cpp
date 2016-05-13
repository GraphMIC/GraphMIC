#include "gmLogicItkLogImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto LogImageFilter::Register =
            Logic::Register<LogImageFilter>("itk",
                                            "LogImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1LogImageFilter.html");
        }
    }
}
