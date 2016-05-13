#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkResampleImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ResampleImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto size = "size";
                    static constexpr auto origin = "origin";
                    static constexpr auto spacing = "spacing";
                    static constexpr auto defaultPixelValue = "default pixel value";
                    static constexpr auto output = "output";
                };

                static Register<ResampleImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ResampleImageFilter() : ImageToImageFilter("ResampleImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("ResampleImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Vector>(ID::size, Data::Optional));
                    this->add(new Slot::Input<Data::Vector>(ID::origin, Data::Optional));
                    this->add(new Slot::Input<Data::Vector>(ID::spacing, Data::Optional));
                    this->add(new Param::Vector(ID::defaultPixelValue, {"r", "g", "b", "a"}, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::ResampleImageFilter<ImageType, ImageType>;

                    auto filter         = FilterType::New();
                    
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto size_vec       = this->getInput<Data::Vector>(ID::size)->getVector();
                    auto origin_vec     = this->getInput<Data::Vector>(ID::origin)->getVector();
                    auto spacing_vec    = this->getInput<Data::Vector>(ID::spacing)->getVector();
                    
                    typename ImageType::SizeType size;
                    typename ImageType::PointType origin;
                    typename ImageType::SpacingType spacing;
                    
                    filter->SetDefaultPixelValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::defaultPixelValue)->getValues()));
                    
                    if (size_vec)
                    {
                        auto values = size_vec->getValues();
                        
                        for (auto i = 0; i < TImage::dimension; ++i)
                        {
                            size[i] = static_cast<typename ImageType::SizeValueType>(values[i]);
                        }
                        
                        filter->SetSize(size);
                    }
                    
                    if (origin_vec)
                    {
                        auto values = origin_vec->getValues();
                        
                        for (auto i = 0; i < TImage::dimension; ++i)
                        {
                            origin[i] = static_cast<typename ImageType::PointValueType>(values[i]);
                        }
                        
                        filter->SetOutputOrigin(origin);
                    }
                    
                    if (spacing_vec)
                    {
                        auto values = spacing_vec->getValues();
                        
                        for (auto i = 0; i < TImage::dimension; ++i)
                        {
                            spacing[i] = static_cast<typename ImageType::SpacingValueType>(values[i]);
                        }
                        
                        filter->SetOutputSpacing(spacing);
                    }
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        auto image = Image::ToItk<ImageType>(it.image());
                        
                        filter->SetInput(image);
                        
                        if (!size_vec) { filter->SetSize(image->GetLargestPossibleRegion().GetSize()); }
                        if (!origin_vec) { filter->SetOutputOrigin(image->GetOrigin()); }
                        if (!spacing_vec) { filter->SetOutputSpacing(image->GetSpacing()); }
                        
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