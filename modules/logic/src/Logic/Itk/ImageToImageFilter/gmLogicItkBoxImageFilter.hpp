#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkBoxImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BoxImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto radius = "radius";
                };
                
                BoxImageFilter(const QString& name) : ImageToImageFilter(name)
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BoxImageFilter");

                    this->add(new Param::Number(ID::radius));
                }
                
                template <class TFilter>
                auto applyParameters(typename TFilter::Pointer filter) -> void
                {
                    log_trace(Log::Func);
                    
                    ImageToImageFilter::applyParameters<TFilter>(filter);
                    filter->SetRadius(this->getParam<Param::Number>(ID::radius)->getValue());
                }
            };
        }
    }
}