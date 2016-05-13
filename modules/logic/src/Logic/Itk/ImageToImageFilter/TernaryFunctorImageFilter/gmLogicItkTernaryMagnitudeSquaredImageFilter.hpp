#pragma once

#include "gmLogicItkTernaryFunctorImageFilter.hpp"

#include <itkTernaryMagnitudeSquaredImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class TernaryMagnitudeSquaredImageFilter : public TernaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto input3 = "input 3";
                    static constexpr auto output = "output";
                };
                
                static Register<TernaryMagnitudeSquaredImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                TernaryMagnitudeSquaredImageFilter() : TernaryFunctorImageFilter("TernaryMagnitudeSquaredImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input3, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::TernaryMagnitudeSquaredImageFilter<ImageType, ImageType, ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput1(Image::ToItk<ImageType>(it.image(0)));
                        filter->SetInput2(Image::ToItk<ImageType>(it.image(1)));
                        filter->SetInput3(Image::ToItk<ImageType>(it.image(2)));
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
