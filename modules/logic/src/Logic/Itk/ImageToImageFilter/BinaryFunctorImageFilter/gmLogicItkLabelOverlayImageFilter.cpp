#include "gmLogicItkLabelOverlayImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto LabelOverlayImageFilter::Register =
            Logic::Register<LabelOverlayImageFilter>("itk",
                                                     "LabelOverlayImageFilter",
                                                     "http://www.itk.org/Doxygen/html/classitk_1_1LabelOverlayImageFilter.html");
        }
    }
}
