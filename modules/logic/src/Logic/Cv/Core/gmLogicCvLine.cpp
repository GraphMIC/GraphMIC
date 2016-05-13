#include "gmLogicCvLine.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Line::Register =
            Logic::Register<Line>("cv",
                                  "line",
                                  "http://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#line");
        }
    }
}
