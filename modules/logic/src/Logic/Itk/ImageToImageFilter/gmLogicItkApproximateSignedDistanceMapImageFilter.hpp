#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkApproximateSignedDistanceMapImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ApproximateSignedDistanceMapImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto insideValue = "insideValue";
                    static constexpr auto outsideValue = "outsideValue";
                    static constexpr auto output = "output";
                };
                
                static Register<ApproximateSignedDistanceMapImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ApproximateSignedDistanceMapImageFilter() : ImageToImageFilter("ApproximateSignedDistanceMapImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("ApproximateSignedDistanceMapImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::insideValue, 1));
                    this->add(new Param::Number(ID::outsideValue, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using OutputType    = itk::Image<float, TImage::dimension>;
                    using FilterType    = itk::ApproximateSignedDistanceMapImageFilter<ImageType, OutputType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetInsideValue(this->getParam<Param::Number>(ID::insideValue)->getValue());
                    filter->SetOutsideValue(this->getParam<Param::Number>(ID::outsideValue)->getValue());
                    
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