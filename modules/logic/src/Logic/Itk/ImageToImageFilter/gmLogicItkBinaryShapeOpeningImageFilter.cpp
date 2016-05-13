#include "gmLogicItkBinaryShapeOpeningImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryShapeOpeningImageFilter::Register =
            Logic::Register<BinaryShapeOpeningImageFilter>("itk",
                                                           "BinaryShapeOpeningImageFilter",
                                                           "http://www.itk.org/Doxygen/html/classitk_1_1BinaryShapeOpeningImageFilter.html");
        }
    }
}
