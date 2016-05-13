#include "gmLogicItkBoxSigmaImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BoxSigmaImageFilter::Register =
            Logic::Register<BoxSigmaImageFilter>("itk",
                                                 "BoxSigmaImageFilter",
                                                 "http://www.itk.org/Doxygen46/html/classitk_1_1BoxSigmaImageFilter.html");
        }
    }
}
