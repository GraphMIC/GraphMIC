#include "gmLogicItkBinaryThinningImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryThinningImageFilter::Register =
            Logic::Register<BinaryThinningImageFilter>("itk",
                                                       "BinaryThinningImageFilter",
                                                       "http://www.itk.org/Doxygen/html/classitk_1_1BinaryThinningImageFilter.html");
        }
    }
}
