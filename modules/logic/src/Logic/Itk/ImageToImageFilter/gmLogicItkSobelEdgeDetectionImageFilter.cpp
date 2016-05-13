#include "gmLogicItkSobelEdgeDetectionImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SobelEdgeDetectionImageFilter::Register =
            Logic::Register<SobelEdgeDetectionImageFilter>("itk",
                                                           "SobelEdgeDetectionImageFilter",
                                                           "http://www.itk.org/Doxygen/html/classitk_1_1SobelEdgeDetectionImageFilter.html");
        }
    }
}
