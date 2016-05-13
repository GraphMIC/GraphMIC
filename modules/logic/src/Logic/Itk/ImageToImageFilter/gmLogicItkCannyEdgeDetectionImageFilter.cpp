#include "gmLogicItkCannyEdgeDetectionImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CannyEdgeDetectionImageFilter::Register =
            Logic::Register<CannyEdgeDetectionImageFilter>("itk",
                                                           "CannyEdgeDetectionImageFilter",
                                                           "http://www.itk.org/Doxygen/html/classitk_1_1CannyEdgeDetectionImageFilter.html");
        }
    }
}
