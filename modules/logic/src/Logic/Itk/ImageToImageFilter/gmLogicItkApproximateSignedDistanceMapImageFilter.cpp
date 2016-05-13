#include "gmLogicItkApproximateSignedDistanceMapImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ApproximateSignedDistanceMapImageFilter::Register =
            Logic::Register<ApproximateSignedDistanceMapImageFilter>("itk",
                                                                     "ApproximateSignedDistanceMapImageFilter",
                                                                     "http://www.itk.org/Doxygen/html/classitk_1_1ApproximateSignedDistanceMapImageFilter.html");
        }
    }
}
