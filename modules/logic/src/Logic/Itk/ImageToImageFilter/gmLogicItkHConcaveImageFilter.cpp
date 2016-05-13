#include "gmLogicItkHConcaveImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HConcaveImageFilter::Register =
            Logic::Register<HConcaveImageFilter>("itk",
                                                 "HConcaveImageFilter",
                                                 "http://www.itk.org/Doxygen/html/classitk_1_1HConcaveImageFilter.html");
        }
    }
}
