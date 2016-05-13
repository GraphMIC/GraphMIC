#include "gmLogicItkHMaximaImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HMaximaImageFilter::Register =
            Logic::Register<HMaximaImageFilter>("itk",
                                                "HMaximaImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1HMaximaImageFilter.html");
        }
    }
}
