#include "gmLogicItkBinaryGrindPeakImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryGrindPeakImageFilter::Register =
            Logic::Register<BinaryGrindPeakImageFilter>("itk",
                                                        "BinaryGrindPeakImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1BinaryGrindPeakImageFilter.html");
        }
    }
}
