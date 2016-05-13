#include "gmLogicItkCropImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CropImageFilter::Register =
            Logic::Register<CropImageFilter>("itk",
                                             "CropImageFilter",
                                             "http://www.itk.org/Doxygen/html/classitk_1_1CropImageFilter.html");
        }
    }
}
