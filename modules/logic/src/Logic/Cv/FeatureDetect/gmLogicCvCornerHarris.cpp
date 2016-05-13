#include "gmLogicCvCornerHarris.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            auto CornerHarris::Register =
            Logic::Register<CornerHarris>("cv",
                                             "CornerHarris",
                                             "http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#cornerharris");
        }
    }
}
