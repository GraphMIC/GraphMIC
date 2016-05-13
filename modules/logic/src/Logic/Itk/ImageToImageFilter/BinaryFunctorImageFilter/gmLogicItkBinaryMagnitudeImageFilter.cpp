#include "gmLogicItkBinaryMagnitudeImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryMagnitudeImageFilter::Register =
            Logic::Register<BinaryMagnitudeImageFilter>("itk",
                                                        "BinaryMagnitudeImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1BinaryMagnitudeImageFilter.html");
        }
    }
}
