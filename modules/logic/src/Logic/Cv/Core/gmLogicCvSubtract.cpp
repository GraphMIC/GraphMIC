#include "gmLogicCvSubtract.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Subtract::Register =
            Logic::Register<Subtract>("cv",
                                 "Subtract",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#subtract");
        }
    }
}

