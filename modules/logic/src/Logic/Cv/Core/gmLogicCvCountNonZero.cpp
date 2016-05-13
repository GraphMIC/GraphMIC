#include "gmLogicCvCountNonZero.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto CountNonZero::Register =
            Logic::Register<CountNonZero>("cv",
                                          "CountNonZero",
                                          "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#countnonzero");
        }
    }
}
