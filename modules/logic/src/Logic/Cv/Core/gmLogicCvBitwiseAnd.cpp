#include "gmLogicCvBitwiseAnd.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto BitwiseAnd::Register =
            Logic::Register<BitwiseAnd>("cv",
                                        "BitwiseAnd",
                                        "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#bitwise-and");
        }
    }
}
