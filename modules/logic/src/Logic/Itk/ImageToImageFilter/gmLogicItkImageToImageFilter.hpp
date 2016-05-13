#pragma once

#include "gmLogicInvoke.hpp"
#include "gmLogicEnable.hpp"
#include "gmLogicItkBase.hpp"

#include "gmDataBase.hpp"
#include "gmDataImage.hpp"
#include "gmDataVector.hpp"

#include <itkImageToImageFilterCommon.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ImageToImageFilter : public Itk::Base
            {
            public:
                struct ID
                {
                    static constexpr auto coordinateTolerance = "coordinate tolerance";
                    static constexpr auto directionTolerance = "direction tolerance";
                };

                ImageToImageFilter(const QString& name) : Itk::Base(name)
                {
                    log_trace(Log::New, this);

                    this->addParamGroup("ImageToImageFilter");

                    this->setRunnable(true);
                    this->setUseTimer(true);

                    this->add(new Param::Number(ID::coordinateTolerance, itk::ImageToImageFilterCommon::GetGlobalDefaultCoordinateTolerance()));
                    this->add(new Param::Number(ID::directionTolerance, itk::ImageToImageFilterCommon::GetGlobalDefaultDirectionTolerance()));
                }

                template <class TFilter>
                auto applyParameters(typename TFilter::Pointer filter) -> void
                {
                    log_trace(Log::Func);

                    filter->SetCoordinateTolerance(this->getParam<Param::Number>(ID::coordinateTolerance)->getValue());
                    filter->SetDirectionTolerance(this->getParam<Param::Number>(ID::directionTolerance)->getValue());
                }

                auto run() -> void override = 0;
            };
        }
    }
}
