#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkCropImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class CropImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto lowerBoundaryCropSize = "lower boundary crop size";
                    static constexpr auto upperBoundaryCropSize = "upper boundary crop size";
                    static constexpr auto output = "output";
                };
                
                static Register<CropImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                CropImageFilter() : ImageToImageFilter("CropImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("CropImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::lowerBoundaryCropSize, {"x", "y", "z"}, 0));
                    this->add(new Param::Vector(ID::upperBoundaryCropSize, {"x", "y", "z"}, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::CropImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto lower_vec      = this->getParam<Param::Vector>(ID::lowerBoundaryCropSize)->getValues();
                    auto upper_vec      = this->getParam<Param::Vector>(ID::upperBoundaryCropSize)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    typename FilterType::SizeType lower;
                    typename FilterType::SizeType upper;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        lower[i] = lower_vec[i];
                    }

                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        upper[i] = upper_vec[i];
                    }
                    
                    filter->SetLowerBoundaryCropSize(lower);
                    filter->SetUpperBoundaryCropSize(upper);
                    
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