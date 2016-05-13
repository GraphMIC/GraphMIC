#include "gmLogicCvAddWeighted.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto AddWeighted::Register =
            Logic::Register<AddWeighted>("cv",
                                         "AddWeighted",
                                         "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#addweighted");
        }
    }
}
