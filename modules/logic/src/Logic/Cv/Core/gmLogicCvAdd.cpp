#include "gmLogicCvAdd.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Add::Register =
            Logic::Register<Add>("cv",
                                 "Add",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#add");
        }
    }
}
