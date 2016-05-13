#include "gmLogicItkBinaryContourImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryContourImageFilter::Register =
            Logic::Register<BinaryContourImageFilter>("itk",
                                                      "BinaryContourImageFilter",
                                                      "http://www.itk.org/Doxygen/html/classitk_1_1BinaryContourImageFilter.html");
        }
    }
}
