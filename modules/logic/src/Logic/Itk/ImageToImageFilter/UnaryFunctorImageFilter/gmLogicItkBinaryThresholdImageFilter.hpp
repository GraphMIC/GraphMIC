#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkBinaryThresholdImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryThresholdImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto lowerThreshold = "lower threshold";
                    static constexpr auto upperThreshold = "upper threshold";
                    static constexpr auto outsideValue = "outside value";
                    static constexpr auto insideValue = "inside value";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryThresholdImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryThresholdImageFilter() : UnaryFunctorImageFilter("BinaryThresholdImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryThresholdImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::lowerThreshold, 0));
                    this->add(new Param::Number(ID::upperThreshold, 1));
                    this->add(new Param::Vector(ID::outsideValue, {"r", "g", "b", "a"}, 0, 0, 0, 1));
                    this->add(new Param::Vector(ID::insideValue, {"r", "g", "b", "a"}, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryThresholdImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetInsideValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::insideValue)->getValues()));
                    filter->SetOutsideValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::outsideValue)->getValues()));
                    filter->SetLowerThreshold(this->getParam<Param::Number>(ID::lowerThreshold)->getValue());
                    filter->SetUpperThreshold(this->getParam<Param::Number>(ID::upperThreshold)->getValue());
                    
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