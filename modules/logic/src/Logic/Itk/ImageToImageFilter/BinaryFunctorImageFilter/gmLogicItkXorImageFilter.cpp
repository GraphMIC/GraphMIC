#include "gmLogicItkXorImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto XorImageFilter::Register =
            Logic::Register<XorImageFilter>("itk",
                                            "XorImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1XorImageFilter.html");
        }
    }
}
