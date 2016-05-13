#include "gmLogicItkBinomialBlurImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto BinomialBlurImageFilter::Register =
            Logic::Register<BinomialBlurImageFilter>("itk",
                                                     "BinomialBlurImageFilter",
                                                     "http://www.itk.org/Doxygen/html/classitk_1_1BinomialBlurImageFilter.html");
        }
    }
}
