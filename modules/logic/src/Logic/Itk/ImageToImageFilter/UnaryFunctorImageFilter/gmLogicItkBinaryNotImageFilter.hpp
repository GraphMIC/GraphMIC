#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkBinaryNotImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryNotImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto foregroundValue = "foreground value";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryNotImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryNotImageFilter() : ImageToImageFilter("BinaryNotImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryNotImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Optional));
                    this->add(new Param::Vector(ID::backgroundValue, {"r", "g", "b", "a"}, 0, 0, 0, 1));
                    this->add(new Param::Vector(ID::foregroundValue, {"r", "g", "b", "a"}, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryNotImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetForegroundValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::foregroundValue)->getValues()));
                    filter->SetBackgroundValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::backgroundValue)->getValues()));
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(0, Image::ToItk<ImageType>(it.image(0)));
                        filter->SetInput(1, Image::ToItk<ImageType>(it.image(1)));
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