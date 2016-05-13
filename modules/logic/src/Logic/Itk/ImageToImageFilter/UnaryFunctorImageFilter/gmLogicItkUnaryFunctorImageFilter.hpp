#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class UnaryFunctorImageFilter : public ImageToImageFilter
            {
            public:
                UnaryFunctorImageFilter(const QString& name) : ImageToImageFilter(name)
                {
                    log_trace(Log::New);
                }
            };
        }
    }
}