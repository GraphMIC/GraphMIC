#include "gmLogicCvScaleAdd.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto ScaleAdd::Register =
            Logic::Register<ScaleAdd>("cv",
                                         "ScaleAdd",
                                         "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#scaleadd");
        }
    }
}
