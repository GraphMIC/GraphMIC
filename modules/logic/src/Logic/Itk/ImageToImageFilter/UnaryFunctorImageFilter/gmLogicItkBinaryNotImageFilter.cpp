#include "gmLogicItkBinaryNotImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryNotImageFilter::Register =
            Logic::Register<BinaryNotImageFilter>("itk",
                                                  "BinaryNotImageFilter",
                                                  "http://www.itk.org/Doxygen/html/classitk_1_1BinaryNotImageFilter.html");
        }
    }
}
