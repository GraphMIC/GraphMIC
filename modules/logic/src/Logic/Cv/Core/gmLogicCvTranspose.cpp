#include "gmLogicCvTranspose.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Transpose::Register =
            Logic::Register<Transpose>("cv",
                                  "Transpose",
                                  "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#transpose");
        }
    }
}
