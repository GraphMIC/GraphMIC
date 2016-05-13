#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkGradientMagnitudeRecursiveGaussianImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class GradientMagnitudeRecursiveGaussianImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto sigma = "sigma";
                    static constexpr auto normalizeAcrossScale = "normalize across scale";
                    static constexpr auto output = "output";
                };
                static Register<GradientMagnitudeRecursiveGaussianImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                GradientMagnitudeRecursiveGaussianImageFilter() : ImageToImageFilter("GradientMagnitudeRecursiveGaussianImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("GradientMagnitudeRecursiveGaussianImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::sigma, 1));
                    this->add(new Param::Bool(ID::normalizeAcrossScale, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::GradientMagnitudeRecursiveGaussianImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    filter->SetSigma(this->getParam<Param::Number>(ID::sigma)->getValue());
                    filter->SetNormalizeAcrossScale(this->getParam<Param::Bool>(ID::normalizeAcrossScale)->getValue());
                    
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
