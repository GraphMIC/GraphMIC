#include "gmLogicCvConvertScaleAbs.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto ConvertScaleAbs::Register =
            Logic::Register<ConvertScaleAbs>("cv",
                                             "ConvertScaleAbs",
                                             "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#convertscaleabs");
        }
    }
}
