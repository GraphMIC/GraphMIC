#include "gmLogicItkConstrainedValueAdditionImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ConstrainedValueAdditionImageFilter::Register =
            Logic::Register<ConstrainedValueAdditionImageFilter>("itk",
                                                                 "ConstrainedValueAdditionImageFilter",
                                                                 "http://www.itk.org/Doxygen/html/classitk_1_1ConstrainedValueAdditionImageFilter.html");
        }
    }
}
