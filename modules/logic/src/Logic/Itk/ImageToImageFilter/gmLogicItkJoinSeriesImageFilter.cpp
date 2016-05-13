#include "gmLogicItkJoinSeriesImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto JoinSeriesImageFilter::Register =
            Logic::Register<JoinSeriesImageFilter>("itk",
                                                   "JoinSeriesImageFilter",
                                                   "http://www.itk.org/Doxygen/html/classitk_1_1JoinSeriesImageFilter.html");
        }
    }
}
