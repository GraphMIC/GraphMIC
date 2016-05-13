#include "gmLogicItkLabelToRGBImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto LabelToRGBImageFilter::Register =
            Logic::Register<LabelToRGBImageFilter>("itk",
                                                   "LabelToRGBImageFilter",
                                                   "http://www.itk.org/Doxygen/html/classitk_1_1LabelToRGBImageFilter.html");
        }
    }
}
