#include "gmLogicCvBitwiseNot.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto BitwiseNot::Register =
            Logic::Register<BitwiseNot>("cv",
                                        "BitwiseNot",
                                        "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#bitwise-not");
        }
    }
}
