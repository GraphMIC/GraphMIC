#pragma once

#include "gmLogicItkBinaryFunctorImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkLabelOverlayImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class LabelOverlayImageFilter : public BinaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto images = "images";
                    static constexpr auto labelImages = "label images";
                    static constexpr auto opacity = "opacity";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto output = "output";
                };
                
                static Register<LabelOverlayImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int>
                >;

                LabelOverlayImageFilter() : BinaryFunctorImageFilter("LabelOverlayImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->addParamGroup("LabelOverlayImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::images, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::labelImages, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::opacity, 0.5));
                    this->add(new Param::Vector(ID::backgroundValue, {"r", "g", "b"} , 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using OutputType    = itk::Image<itk::RGBPixel<typename ImageType::PixelType>, TImage::dimension>;
                    using FilterType    = itk::LabelOverlayImageFilter<ImageType, ImageType, OutputType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto color_vec      = this->getParam<Param::Vector>(ID::backgroundValue)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetOpacity(this->getParam<Param::Number>(ID::opacity)->getValue());
                    filter->SetBackgroundValue(Util::VectorToPixel<typename FilterType::LabelPixelType>(color_vec));
                    filter->SetLabelImage(Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::labelImages)->getImage()));
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(Image::ToItk<ImageType>(it.image()));
                        filter->Update();
                        output->addImage(Image::FromItk<OutputType>(filter->GetOutput()));
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