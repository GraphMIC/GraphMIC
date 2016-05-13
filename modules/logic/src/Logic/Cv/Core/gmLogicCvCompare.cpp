#include "gmLogicCvCompare.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Compare::Register =
            Logic::Register<Compare>("cv",
                                     "Compare",
                                     "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#compare");
        }
    }
}
