#include "gmLogicCvAbs.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Abs::Register =
            Logic::Register<Abs>("cv",
                                 "Abs",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#abs");
        }
    }
}
