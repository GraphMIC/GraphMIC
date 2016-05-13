#include "gmLogicItkHMinimaImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto HMinimaImageFilter::Register =
            Logic::Register<HMinimaImageFilter>("itk",
                                                "HMinimaImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1HMinimaImageFilter.html");
        }
    }
}
