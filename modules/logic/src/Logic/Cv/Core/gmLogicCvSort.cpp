#include "gmLogicCvSort.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Sort::Register =
            Logic::Register<Sort>("cv",
                                 "Sort",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#sort");
        }
    }
}
