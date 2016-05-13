#include "gmLogicItkBinShrinkImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinShrinkImageFilter::Register =
            Logic::Register<BinShrinkImageFilter>("itk",
                                                 "BinShrinkImageFilter",
                                                 "http://www.itk.org/Doxygen/html/classitk_1_1BinaryFillholeImageFilter.html");
        }
    }
}
