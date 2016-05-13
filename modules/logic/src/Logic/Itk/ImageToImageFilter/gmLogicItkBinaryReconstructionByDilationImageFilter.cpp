#include "gmLogicItkBinaryReconstructionByDilationImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinaryReconstructionByDilationImageFilter::Register =
            Logic::Register<BinaryReconstructionByDilationImageFilter>("itk",
                                                                       "BinaryReconstructionByDilationImageFilter",
                                                                       "http://www.itk.org/Doxygen/html/classitk_1_1BinaryReconstructionByDilationImageFilter.html");
        }
    }
}
