#include "gmLogicItkBinaryFillholeImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryFillholeImageFilter::Register =
            Logic::Register<BinaryFillholeImageFilter>("itk",
                                                       "BinaryFillholeImageFilter",
                                                       "http://www.itk.org/Doxygen/html/classitk_1_1BinaryFillholeImageFilter.html");
        }
    }
}
