#include "gmLogicCvSplit.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Split::Register =
            Logic::Register<Split>("cv",
                                   "Split",
                                   "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#split");
        }
    }
}
