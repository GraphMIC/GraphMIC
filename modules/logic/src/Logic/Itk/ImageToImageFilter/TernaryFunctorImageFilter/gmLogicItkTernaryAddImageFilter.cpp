#include "gmLogicItkTernaryAddImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto TernaryAddImageFilter::Register =
            Logic::Register<TernaryAddImageFilter>("itk",
                                                   "TernaryAddImageFilter",
                                                   "http://www.itk.org/Doxygen/html/classitk_1_1TernaryAddImageFilter.html");
        }
    }
}