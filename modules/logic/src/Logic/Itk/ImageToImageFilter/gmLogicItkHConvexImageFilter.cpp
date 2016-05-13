#include "gmLogicItkHConvexImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HConvexImageFilter::Register =
            Logic::Register<HConvexImageFilter>("itk",
                                                "HConvexImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1HConvexImageFilter.html");
        }
    }
}
