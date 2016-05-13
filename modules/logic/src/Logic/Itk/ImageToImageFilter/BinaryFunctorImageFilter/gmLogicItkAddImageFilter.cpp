#include "gmLogicItkAddImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto AddImageFilter::Register =
            Logic::Register<AddImageFilter>("itk",
                                            "AddImageFilter",
                                            "http://www.itk.org/Doxygen/html/classitk_1_1AddImageFilter.html");
        }
    }
}
