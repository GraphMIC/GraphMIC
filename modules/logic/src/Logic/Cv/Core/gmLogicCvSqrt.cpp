#include "gmLogicCvSqrt.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Sqrt::Register =
            Logic::Register<Sqrt>("cv",
                                 "Sqrt",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#sqrt");
        }
    }
}
