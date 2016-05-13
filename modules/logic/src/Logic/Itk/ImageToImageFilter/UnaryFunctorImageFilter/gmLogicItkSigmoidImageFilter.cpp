#include "gmLogicItkSigmoidImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto SigmoidImageFilter::Register =
            Logic::Register<SigmoidImageFilter>("itk",
                                                "SigmoidImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1SigmoidImageFilter.html");
        }
    }
}
