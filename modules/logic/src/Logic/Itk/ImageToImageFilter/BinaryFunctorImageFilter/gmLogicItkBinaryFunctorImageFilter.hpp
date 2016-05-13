#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryFunctorImageFilter : public ImageToImageFilter
            {
            public:
                BinaryFunctorImageFilter(const QString& name) : ImageToImageFilter(name)
                {
                    log_trace(Log::New, this);
                }
            };
        }
    }
}