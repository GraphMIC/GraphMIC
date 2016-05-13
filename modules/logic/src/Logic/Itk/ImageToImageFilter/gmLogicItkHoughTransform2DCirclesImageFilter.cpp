#include "gmLogicItkHoughTransform2DCirclesImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HoughTransform2DCirclesImageFilter::Register =
            Logic::Register<HoughTransform2DCirclesImageFilter>("itk",
                                                                "HoughTransform2DCirclesImageFilter",
                                                                "http://www.itk.org/Doxygen/html/classitk_1_1HoughTransform2DCirclesImageFilter.html");
        }
    }
}
