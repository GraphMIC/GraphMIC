#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkSigmoidImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class SigmoidImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto alpha = "alpha";
                    static constexpr auto beta = "beta";
                    static constexpr auto outputMinimum = "output minimum";
                    static constexpr auto outputMaximum = "output maximum";
                    static constexpr auto output = "output";
                };
                
                static Register<SigmoidImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                SigmoidImageFilter() : ImageToImageFilter("SigmoidImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("SigmoidImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::alpha, 1));
                    this->add(new Param::Number(ID::beta, 0));
                    this->add(new Param::Number(ID::outputMinimum, 0));
                    this->add(new Param::Number(ID::outputMaximum, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::SigmoidImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetAlpha(this->getParam<Param::Number>(ID::alpha)->getValue());
                    filter->SetBeta(this->getParam<Param::Number>(ID::beta)->getValue());
                    filter->SetOutputMinimum(this->getParam<Param::Number>(ID::outputMinimum)->getValue());
                    filter->SetOutputMaximum(this->getParam<Param::Number>(ID::outputMaximum)->getValue());
                    
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