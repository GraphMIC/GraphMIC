#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"

#include <itkInvertIntensityImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class InvertIntensityImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto maximum = "maximum";
                    static constexpr auto output = "output";
                };
                
                static Register<InvertIntensityImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                InvertIntensityImageFilter() : UnaryFunctorImageFilter("InvertIntensityImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("InvertIntensityImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::maximum, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::InvertIntensityImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto max            = this->getParam<Param::Number>(ID::maximum)->getValue();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetMaximum(max);
                    
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