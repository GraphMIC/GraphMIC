#include "gmLogicItkModulusImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ModulusImageFilter::Register =
            Logic::Register<ModulusImageFilter>("itk",
                                                "ModulusImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1ModulusImageFilter.html");
        }
    }
}
