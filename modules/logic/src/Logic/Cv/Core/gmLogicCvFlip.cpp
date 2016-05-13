#include "gmLogicCvFlip.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Flip::Register =
            Logic::Register<Flip>("cv",
                                  "Flip",
                                  "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#flip");
        }
    }
}
