#include "gmLogicCvHoughLines.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto HoughLines::Register =
            Logic::Register<HoughLines>("cv",
                                 "HoughLines",
                                 "http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#houghlines");
        }
    }
}
