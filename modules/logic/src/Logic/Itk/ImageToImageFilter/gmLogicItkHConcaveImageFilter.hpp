#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkHConcaveImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class HConcaveImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto height = "height";
                    static constexpr auto fullyConnected = "fully connected";
                    static constexpr auto output = "output";
                };
                
                static Register<HConcaveImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                HConcaveImageFilter() : ImageToImageFilter("HConcaveImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("HConcaveImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::height, 2));
                    this->add(new Param::Bool(ID::fullyConnected, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::HConcaveImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetHeight(this->getParam<Param::Number>(ID::height)->getValue());
                    filter->SetFullyConnected(this->getParam<Param::Bool>(ID::fullyConnected)->getValue());
                    
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