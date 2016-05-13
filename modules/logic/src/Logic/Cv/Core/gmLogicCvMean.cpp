#include "gmLogicCvMean.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Mean::Register =
            Logic::Register<Mean>("cv",
                                  "Mean",
                                  "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#mean");
        }
    }
}
