#include "gmLogicItkCosImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CosImageFilter::Register =
            Logic::Register<CosImageFilter>("itk",
                                            "CosImageFilter",
                                            "http://www.itk.org/Doxygen46/html/classitk_1_1CosImageFilter.html");
        }
    }
}
