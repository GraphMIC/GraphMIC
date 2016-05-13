#include "gmLogicItkBoxMeanImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BoxMeanImageFilter::Register =
            Logic::Register<BoxMeanImageFilter>("itk",
                                                "BoxMeanImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1BoxMeanImageFilter.html");
        }
    }
}
