#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class NaryFunctorImageFilter : public ImageToImageFilter
            {
            public:
                NaryFunctorImageFilter(const QString& name) : ImageToImageFilter(name)
                {
                    log_trace(Log::New);
                }
            };
        }
    }
}