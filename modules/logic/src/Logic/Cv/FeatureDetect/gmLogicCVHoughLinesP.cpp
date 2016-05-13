#include "gmLogicCvHoughLinesP.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto HoughLinesP::Register =
            Logic::Register<HoughLinesP>("cv",
                                        "HoughLinesP",
                                        "http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#houghlinesp");
        }
    }
}
