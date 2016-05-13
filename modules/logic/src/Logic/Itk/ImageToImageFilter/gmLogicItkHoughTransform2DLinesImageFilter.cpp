#include "gmLogicItkHoughTransform2DLinesImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HoughTransform2DLinesImageFilter::Register =
            Logic::Register<HoughTransform2DLinesImageFilter>("itk",
                                                              "HoughTransform2DLinesImageFilter",
                                                              "http://www.itk.org/Doxygen/html/classitk_1_1HoughTransform2DLinesImageFilter.html");
        }
    }
}
