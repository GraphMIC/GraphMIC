#include "gmLogicItkThresholdImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ThresholdImageFilter::Register =
            Logic::Register<ThresholdImageFilter>("itk",
                                                  "ThresholdImageFilter",
                                                  "http://www.itk.org/Doxygen/html/classitk_1_1ThresholdImageFilter.html");
        }
    }
}
