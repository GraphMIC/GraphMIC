#include "gmLogicItkChangeInformationImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto ChangeInformationImageFilter::Register =
            Logic::Register<ChangeInformationImageFilter>("itk",
                                                          "ChangeInformationImageFilter",
                                                          "http://www.itk.org/Doxygen/html/classitk_1_1ChangeInformationImageFilter.html");
        }
    }
}
