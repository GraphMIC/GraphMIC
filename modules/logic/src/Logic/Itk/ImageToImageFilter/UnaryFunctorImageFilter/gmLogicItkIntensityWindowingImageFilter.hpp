#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"

#include <itkIntensityWindowingImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class IntensityWindowingImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto level = "level";
                    static constexpr auto window = "window";
                    static constexpr auto windowMinimum = "window minimum";
                    static constexpr auto windowMaximum = "window maximum";
                    static constexpr auto outputMinimum = "output minimum";
                    static constexpr auto outputMaximum = "output maximum";
                    static constexpr auto output = "output";
                };
                
                static Register<IntensityWindowingImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                IntensityWindowingImageFilter() : UnaryFunctorImageFilter("IntensityWindowingImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("IntensityWindowingImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::level, 0));
                    this->add(new Param::Number(ID::window, 0));
                    this->add(new Param::Number(ID::windowMinimum, 0));
                    this->add(new Param::Number(ID::windowMaximum, 1));
                    this->add(new Param::Number(ID::outputMinimum, 0));
                    this->add(new Param::Number(ID::outputMaximum, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::IntensityWindowingImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetWindowLevel(this->getParam<Param::Number>(ID::level)->getValue(), this->getParam<Param::Number>(ID::window)->getValue());
                    filter->SetWindowMinimum(this->getParam<Param::Number>(ID::windowMinimum)->getValue());
                    filter->SetWindowMaximum(this->getParam<Param::Number>(ID::windowMaximum)->getValue());
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