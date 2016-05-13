#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkThresholdImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ThresholdImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto thresholdType = "threshold";
                    static constexpr auto lower = "lower";
                    static constexpr auto upper = "upper";
                    static constexpr auto outsideValue = "outside value";
                    static constexpr auto output = "output";
                };
                
                static Register<ThresholdImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ThresholdImageFilter() : ImageToImageFilter("ThresholdImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("ThresholdImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::thresholdType, {"below", "between", "above"}));
                    this->add(new Param::Number(ID::lower, 0));
                    this->add(new Param::Number(ID::upper, 1));
                    this->add(new Param::Number(ID::outsideValue));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::ThresholdImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto lower          = this->getParam<Param::Number>(ID::lower)->getValue();
                    auto upper          = this->getParam<Param::Number>(ID::upper)->getValue();
                    auto type           = this->getParam<Param::Option>(ID::thresholdType)->getIndex();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetOutsideValue(this->getParam<Param::Number>(ID::outsideValue)->getValue());

                    if (type == 0) { filter->ThresholdBelow(lower); }
                    else if (type == 1) { filter->ThresholdOutside(lower, upper); }
                    else { filter->ThresholdAbove(upper); }
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(Image::ToItk<ImageType>(it.image()));
                        filter->Update();
                        output->addImage(Image::FromItk<ImageType>(filter->GetOutput()));
                    }
                }
                
                auto run() -> void override
                {
                    log_trace(Log::Func);
                    
                    Invoke(this);
                }
            };
        }
    }
}