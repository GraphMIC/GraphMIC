#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class TernaryFunctorImageFilter : public ImageToImageFilter
            {
            public:
                TernaryFunctorImageFilter(const QString& name) : ImageToImageFilter(name)
                {
                    log_trace(Log::New);
                }
            };
        }
    }
}