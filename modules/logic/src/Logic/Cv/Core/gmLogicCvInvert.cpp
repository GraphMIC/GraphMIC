#include "gmLogicCvInvert.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Invert::Register =
            Logic::Register<Invert>("cv",
                                    "Invert",
                                    "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#invert");
        }
    }
}
