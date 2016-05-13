#include "gmLogicItkExpImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ExpImageFilter::Register =
            Logic::Register<ExpImageFilter>("itk",
                                            "ExpImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1ExpImageFilter.html");
        }
    }
}
