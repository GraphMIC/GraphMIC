#include "gmLogicCvDivide.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Divide::Register =
            Logic::Register<Divide>("cv",
                                    "Divide",
                                    "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#divide");
        }
    }
}
