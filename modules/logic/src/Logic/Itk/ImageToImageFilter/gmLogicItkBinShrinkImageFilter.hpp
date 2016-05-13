#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkBinShrinkImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinShrinkImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto shrinkFactors = "shrink factors";
                    static constexpr auto output = "output";
                };

                static Register<BinShrinkImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinShrinkImageFilter() : ImageToImageFilter("BinShrinkImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinShrinkImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::shrinkFactors, {"x", "y", "z"}, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinShrinkImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto factors_vec    = this->getParam<Param::Vector>(ID::shrinkFactors)->getValues();
                    
                    applyParameters<FilterType>(filter);
                    
                    typename FilterType::ShrinkFactorsType factors;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        factors[i] = factors_vec[i];
                    }
                    
                    filter->SetShrinkFactors(factors);
                    
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