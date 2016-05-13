#include "gmLogicCvPreCornerDetect.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto PreCornerDetect::Register =
            Logic::Register<PreCornerDetect>("cv",
                                   "PreCornerDetect",
                                   "http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#precornerdetect");
        }
    }
}
