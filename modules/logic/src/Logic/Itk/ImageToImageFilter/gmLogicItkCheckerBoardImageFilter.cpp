#include "gmLogicItkCheckerBoardImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto CheckerBoardImageFilter::Register =
            Logic::Register<CheckerBoardImageFilter>("itk",
                                                     "CheckerBoardImageFilter",
                                                     "http://www.itk.org/Doxygen/html/classitk_1_1CheckerBoardImageFilter.html");
        }
    }
}
