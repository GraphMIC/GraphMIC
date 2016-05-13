#include "gmLogicItkBinaryReconstructionByErosionImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryReconstructionByErosionImageFilter::Register =
            Logic::Register<BinaryReconstructionByErosionImageFilter>("itk",
                                                                      "BinaryReconstructionByErosionImageFilter",
                                                                      "http://www.itk.org/Doxygen44/html/classitk_1_1BinaryReconstructionByErosionImageFilter.html");
        }
    }
}
