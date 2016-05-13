#include "gmLogicCvDeterminant.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Determinant::Register =
            Logic::Register<Determinant>("cv",
                                         "Determinant",
                                         "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#determinant");
        }
    }
}
