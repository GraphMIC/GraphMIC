#include "gmLogicItkSqrtImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SqrtImageFilter::Register =
            Logic::Register<SqrtImageFilter>("itk",
                                             "SqrtImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1SqrtImageFilter.html");
        }
    }
}
