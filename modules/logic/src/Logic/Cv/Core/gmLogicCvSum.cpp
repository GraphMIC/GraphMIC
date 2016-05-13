#include "gmLogicCvSum.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Sum::Register =
            Logic::Register<Sum>("cv",
                                         "Sum",
                                         "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#sum");
        }
    }
}
