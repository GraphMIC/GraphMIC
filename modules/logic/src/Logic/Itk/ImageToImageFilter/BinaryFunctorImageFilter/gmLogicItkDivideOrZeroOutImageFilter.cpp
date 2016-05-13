#include "gmLogicItkDivideOrZeroOutImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto DivideOrZeroOutImageFilter::Register =
            Logic::Register<DivideOrZeroOutImageFilter>("itk",
                                                        "DivideOrZeroOutImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1DivideOrZeroOutImageFilter.html");
        }
    }
}
