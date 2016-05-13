#include "gmLogicItkBinaryThresholdImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryThresholdImageFilter::Register =
            Logic::Register<BinaryThresholdImageFilter>("itk",
                                                        "BinaryThresholdImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1BinaryThresholdImageFilter.html");
        }
    }
}
