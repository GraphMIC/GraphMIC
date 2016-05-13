#include "gmLogicCvBitwiseOr.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto BitwiseOr::Register =
            Logic::Register<BitwiseOr>("cv",
                                       "BitwiseOr",
                                       "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#bitwise-or");
        }
    }
}
