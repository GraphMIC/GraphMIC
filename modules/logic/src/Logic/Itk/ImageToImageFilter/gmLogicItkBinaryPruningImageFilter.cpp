#include "gmLogicItkBinaryPruningImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryPruningImageFilter::Register =
            Logic::Register<BinaryPruningImageFilter>("itk",
                                                      "BinaryPruningImageFilter",
                                                      "http://www.itk.org/Doxygen/html/classitk_1_1BinaryPruningImageFilter.html");
        }
    }
}
