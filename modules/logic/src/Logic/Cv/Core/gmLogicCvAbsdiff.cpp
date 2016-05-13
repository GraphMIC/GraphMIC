#include "gmLogicCvAbsdiff.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Absdiff::Register =
            Logic::Register<Absdiff>("cv",
                                     "AbsDiff",
                                     "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#absdiff");
        }
    }
}
