#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkFlipImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class FlipImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto flipAxes = "flip axes";
                    static constexpr auto flipAboutOrigin = "flip about origin";
                    static constexpr auto output = "output";
                };
                
                static Register<FlipImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                FlipImageFilter() : ImageToImageFilter("FlipImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("FlipImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::flipAxes, {"x", "y", "z"}, 0));
                    this->add(new Param::Bool(ID::flipAboutOrigin, true));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::FlipImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto axes_vec       = this->getParam<Param::Vector>(ID::flipAxes)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    typename FilterType::FlipAxesArrayType axes;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        axes[i] = axes_vec[i];
                    }
                    
                    filter->SetFlipAboutOrigin(this->getParam<Param::Bool>(ID::flipAboutOrigin)->getValue());
                    filter->SetFlipAxes(axes);
                    
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