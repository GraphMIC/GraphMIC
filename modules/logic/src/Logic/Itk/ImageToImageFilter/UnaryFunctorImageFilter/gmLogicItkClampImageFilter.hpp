#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"

#include <itkClampImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ClampImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto lowerBound = "lower bound";
                    static constexpr auto upperBound = "upper bound";
                    static constexpr auto output = "output";
                };
                
                static Register<ClampImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ClampImageFilter() : UnaryFunctorImageFilter("ClampImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("ClampImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::lowerBound, 0));
                    this->add(new Param::Number(ID::upperBound, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::ClampImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetBounds(this->getParam<Param::Number>(ID::lowerBound)->getValue(), this->getParam<Param::Number>(ID::upperBound)->getValue());
                    
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