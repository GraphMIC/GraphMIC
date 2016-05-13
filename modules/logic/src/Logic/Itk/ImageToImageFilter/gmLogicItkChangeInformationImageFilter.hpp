#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkChangeInformationImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ChangeInformationImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto referenceImage = "reference image";
                    static constexpr auto transform = "transform";
                    static constexpr auto origin = "origin";
                    static constexpr auto spacing = "spacing";
                    static constexpr auto offset = "offset";
                    static constexpr auto centerImage = "center image";
                    static constexpr auto output = "output";
                };
                
                static Register<ChangeInformationImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ChangeInformationImageFilter() : ImageToImageFilter("ChangeInformationImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("ChangeInformationImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::referenceImage, Access::MakeConstraints(), Data::Optional));
                    this->add(new Slot::Input<Data::Vector>(ID::origin, Data::Optional));
                    this->add(new Slot::Input<Data::Vector>(ID::spacing, Data::Optional));
                    this->add(new Slot::Input<Data::Vector>(ID::offset, Data::Optional));
                    this->add(new Param::Bool(ID::centerImage, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::ChangeInformationImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto origin_vec     = this->getInput<Data::Vector>(ID::origin)->getVector();
                    auto spacing_vec    = this->getInput<Data::Vector>(ID::spacing)->getVector();
                    auto offset_vec     = this->getInput<Data::Vector>(ID::offset)->getVector();
                    auto referenceImage = Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::referenceImage)->getImage());
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    typename ImageType::OffsetType offset;
                    typename ImageType::PointType origin;
                    typename ImageType::SpacingType spacing;
                    typename ImageType::DirectionType direction;
                    
                    filter->SetUseReferenceImage(referenceImage);
                    filter->SetCenterImage(this->getParam<Param::Bool>(ID::centerImage)->getValue());
                    
                    if (offset_vec)
                    {
                        auto values = offset_vec->getValues();
                        
                        for (auto i = 0; i < TImage::dimension; ++i)
                        {
                            offset[i] = values[i];
                        }
                    }
                    
                    if (!referenceImage)
                    {
                        filter->SetChangeOrigin(origin_vec);
                        filter->SetChangeSpacing(spacing_vec);
                        
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
                    }
                    else
                    {
                        filter->SetReferenceImage(referenceImage);
                    }
                    
                    for (auto it : this->inputIterator())
                    {
                        auto image = Image::ToItk<ImageType>(it.image());
                        
                        filter->SetInput(image);
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