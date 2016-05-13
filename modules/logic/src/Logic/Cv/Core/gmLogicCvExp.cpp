#include "gmLogicCvExp.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Exp::Register =
            Logic::Register<Exp>("cv",
                                 "Exp",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#exp");
        }
    }
}
