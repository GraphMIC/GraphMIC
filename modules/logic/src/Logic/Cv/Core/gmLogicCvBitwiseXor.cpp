#include "gmLogicCvBitwiseXor.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto BitwiseXor::Register =
            Logic::Register<BitwiseXor>("cv",
                                        "BitwiseXor",
                                        "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#bitwise-xor");
        }
    }
}
