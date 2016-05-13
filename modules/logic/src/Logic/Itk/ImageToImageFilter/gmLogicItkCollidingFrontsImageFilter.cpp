#include "gmLogicItkCollidingFrontsImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CollidingFrontsImageFilter::Register =
            Logic::Register<CollidingFrontsImageFilter>("itk",
                                                        "CollidingFrontsImageFilter",
                                                        "http://www.itk.org/Doxygen/html/classitk_1_1CollidingFrontsImageFilter.html");
        }
    }
}
