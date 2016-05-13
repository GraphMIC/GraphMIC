#pragma once

#include "gmLogicItkNaryFunctorImageFilter.hpp"

#include <itkNaryAddImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class NaryAddImageFilter : public NaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "output";
                };
                
                static Register<NaryAddImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                NaryAddImageFilter() : NaryFunctorImageFilter("NaryAddImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::NaryAddImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(it.iteration(), Image::ToItk<ImageType>(it.image()));

                    }
                    
                    filter->Update();
                    output->addImage(Image::FromItk<ImageType>(filter->GetOutput()));
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
