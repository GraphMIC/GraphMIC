#include "gmLogicCvLog.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Log::Register =
            Logic::Register<Log>("cv",
                                 "Log",
                                 "http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#log");
        }
    }
}
