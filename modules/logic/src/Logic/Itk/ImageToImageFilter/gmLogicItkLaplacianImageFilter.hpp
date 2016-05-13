#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkLaplacianImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class LaplacianImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto useImageSpacing = "spacing";
                    static constexpr auto output = "output";
                };
                
                static Register<LaplacianImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<float, double>
                >;

                LaplacianImageFilter() : ImageToImageFilter("LaplacianImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("LaplacianImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Bool(ID::useImageSpacing, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::LaplacianImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetUseImageSpacing(this->getParam<Param::Bool>(ID::useImageSpacing)->getValue());
                    
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