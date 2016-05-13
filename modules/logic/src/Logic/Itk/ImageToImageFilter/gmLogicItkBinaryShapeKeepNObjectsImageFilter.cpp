#include "gmLogicItkBinaryShapeKeepNObjectsImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryShapeKeepNObjectsImageFilter::Register =
            Logic::Register<BinaryShapeKeepNObjectsImageFilter>("itk",
                                                                "BinaryShapeKeepNObjectsImageFilter",
                                                                "http://www.itk.org/Doxygen/html/classitk_1_1BinaryShapeKeepNObjectsImageFilter.html");
        }
    }
}
