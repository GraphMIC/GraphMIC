#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkLabelToRGBImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class LabelToRGBImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto backgroundColor = "background color";
                    static constexpr auto output = "output";
                };
                
                static Register<LabelToRGBImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int>
                >;

                using Output = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int>
                >;

                LabelToRGBImageFilter() : UnaryFunctorImageFilter("LabelToRGBImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("LabelToRGBImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::backgroundColor, {"r", "g", "b"} , 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Output::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using OutputType    = itk::Image<itk::RGBPixel<typename ImageType::PixelType>, TImage::dimension>;
                    using FilterType    = itk::LabelToRGBImageFilter<ImageType, OutputType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto color_vec      = this->getParam<Param::Vector>(ID::backgroundColor)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetBackgroundColor(Util::VectorToPixel<typename OutputType::PixelType>(color_vec));
                    
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