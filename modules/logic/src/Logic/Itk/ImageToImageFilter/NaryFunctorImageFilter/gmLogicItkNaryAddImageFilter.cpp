#include "gmLogicItkNaryAddImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto NaryAddImageFilter::Register =
            Logic::Register<NaryAddImageFilter>("itk",
                                                "NaryAddImageFilter",
                                                "http://www.itk.org/Doxygen/html/classitk_1_1NaryAddImageFilter.html");
        }
    }
}