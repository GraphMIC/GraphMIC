#include "gmLogicCvCanny.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto Canny::Register =
            Logic::Register<Canny>("cv",
                                        "Canny",
                                        "http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#canny");
        }
    }
}
