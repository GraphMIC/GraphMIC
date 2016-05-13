#include "gmLogicItkAtan2ImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto Atan2ImageFilter::Register =
            Logic::Register<Atan2ImageFilter>("itk",
                                              "Atan2ImageFilter",
                                              "http://www.itk.org/Doxygen/html/classitk_1_1Atan2ImageFilter.html");
        }
    }
}
