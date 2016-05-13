#include "gmLogicItkBinaryMedianImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryMedianImageFilter::Register =
            Logic::Register<BinaryMedianImageFilter>("itk",
                                                     "BinaryMedianImageFilter",
                                                     "http://www.itk.org/Doxygen/html/classitk_1_1BinaryMedianImageFilter.html");
        }
    }
}
