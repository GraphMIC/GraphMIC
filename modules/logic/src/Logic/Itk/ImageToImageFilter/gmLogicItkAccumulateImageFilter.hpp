#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkAccumulateImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class AccumulateImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto average = "average";
                    static constexpr auto output = "output";
                    static constexpr auto accumulateDimension = "accumulate dimension";
                };

                static Register<AccumulateImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;
                
                AccumulateImageFilter() : ImageToImageFilter("AccumulateImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("AccumulateImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::accumulateDimension, 0));
                    this->add(new Param::Bool(ID::average, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {   
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::AccumulateImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetAverage(this->getParam<Param::Bool>(ID::average)->getValue());
                    filter->SetAccumulateDimension(this->getParam<Param::Number>(ID::accumulateDimension)->getValue());
                    
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