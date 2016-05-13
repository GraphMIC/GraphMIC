#include "gmLogicItkLog10ImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto Log10ImageFilter::Register =
            Logic::Register<Log10ImageFilter>("itk",
                                              "Log10ImageFilter",
                                              "http://www.itk.org/Doxygen/html/classitk_1_1Log10ImageFilter.html");
        }
    }
}
