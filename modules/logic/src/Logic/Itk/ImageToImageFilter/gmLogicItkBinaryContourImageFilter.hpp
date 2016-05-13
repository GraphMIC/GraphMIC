#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkBinaryContourImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryContourImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto foregroundValue = "foreground value";
                    static constexpr auto fullyConnected = "fully connected";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryContourImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryContourImageFilter() : ImageToImageFilter("BinaryContourImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryContourImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::backgroundValue, {"r", "g", "b", "a"}, 0, 0, 0, 1));
                    this->add(new Param::Vector(ID::foregroundValue, {"r", "g", "b", "a"}, 1));
                    this->add(new Param::Bool(ID::fullyConnected, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryContourImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto background_vec = this->getParam<Param::Vector>(ID::backgroundValue)->getValues();
                    auto foreground_vec = this->getParam<Param::Vector>(ID::foregroundValue)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetFullyConnected(this->getParam<Param::Bool>(ID::fullyConnected)->getValue());
                    
                    filter->SetForegroundValue(Util::VectorToPixel<typename ImageType::PixelType>(foreground_vec));
                    filter->SetBackgroundValue(Util::VectorToPixel<typename ImageType::PixelType>(background_vec));
                    
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