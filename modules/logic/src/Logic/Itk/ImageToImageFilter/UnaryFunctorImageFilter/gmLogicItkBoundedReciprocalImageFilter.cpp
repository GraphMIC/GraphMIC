#include "gmLogicItkBoundedReciprocalImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BoundedReciprocalImageFilter::Register =
            Logic::Register<BoundedReciprocalImageFilter>("itk",
                                                          "BoundedReciprocalImageFilter",
                                                          "http://www.itk.org/Doxygen/html/classitk_1_1BoundedReciprocalImageFilter.html");
        }
    }
}
