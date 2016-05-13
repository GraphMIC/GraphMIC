#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkCannyEdgeDetectionImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class CannyEdgeDetectionImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto lowerThreshold = "lower threshold";
                    static constexpr auto upperThreshold = "upper threshold";
                    static constexpr auto maximumError = "maximum error";
                    static constexpr auto variance = "variance";
                    static constexpr auto output = "output";
                };
                
                static Register<CannyEdgeDetectionImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<float, double>
                >;

                CannyEdgeDetectionImageFilter() : ImageToImageFilter("CannyEdgeDetectionImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->addParamGroup("CannyEdgeDetectionImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::lowerThreshold, 0));
                    this->add(new Param::Number(ID::upperThreshold, 1));
                    this->add(new Param::Vector(ID::maximumError, {"x", "y", "z"}, 0.1));
                    this->add(new Param::Vector(ID::variance, {"x", "y", "z"}));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::CannyEdgeDetectionImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto error_vec      = this->getParam<Param::Vector>(ID::maximumError)->getValues();
                    auto variance_vec   = this->getParam<Param::Vector>(ID::variance)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetLowerThreshold(this->getParam<Param::Number>(ID::lowerThreshold)->getValue());
                    filter->SetLowerThreshold(this->getParam<Param::Number>(ID::upperThreshold)->getValue());
                    
                    typename FilterType::ArrayType error;
                    typename FilterType::ArrayType variance;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        error[i] = error_vec[i];
                    }
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        variance[i] = variance_vec[i];
                    }
                    
                    filter->SetMaximumError(error);
                    filter->SetVariance(variance);
                    
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