#pragma once

#include "gmLogicItkBinaryFunctorImageFilter.hpp"

#include <itkAtan2ImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class Atan2ImageFilter : public BinaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto output = "output";
                };
                
                static Register<Atan2ImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                Atan2ImageFilter() : BinaryFunctorImageFilter("Atan2ImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::Atan2ImageFilter<ImageType, ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    BinaryFunctorImageFilter::applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput1(Image::ToItk<ImageType>(it.image(0)));
                        filter->SetInput2(Image::ToItk<ImageType>(it.image(1)));
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
