#include "gmLogicItkMeanImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto MeanImageFilter::Register =
            Logic::Register<MeanImageFilter>("itk",
                                             "MeanImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1MeanImageFilter.html");
        }
    }
}
