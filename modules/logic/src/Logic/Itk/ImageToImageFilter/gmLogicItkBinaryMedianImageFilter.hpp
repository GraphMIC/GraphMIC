#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkBinaryMedianImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryMedianImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto radius = "radius";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto output = "output";
                };

                static Register<BinaryMedianImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryMedianImageFilter() : ImageToImageFilter("BinaryMedianImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryMedianImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::radius, {"x", "y", "z"}, 1));
                    this->add(new Param::Vector(ID::backgroundValue, {"r", "g", "b", "a"}, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryMedianImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto radius_vec     = this->getParam<Param::Vector>(ID::radius)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    typename FilterType::InputSizeType radius;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        radius[i] = radius_vec[i];
                    }
                    
                    filter->SetRadius(radius);
                    filter->SetBackgroundValue(Util::VectorToPixel<typename FilterType::InputPixelType>(this->getParam<Param::Vector>(ID::backgroundValue)->getValues()));
                    
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