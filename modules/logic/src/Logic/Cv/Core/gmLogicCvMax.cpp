#include "gmLogicCvMax.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Max::Register =
            Logic::Register<Max>("cv",
                                 "Max",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#max");
        }
    }
}
