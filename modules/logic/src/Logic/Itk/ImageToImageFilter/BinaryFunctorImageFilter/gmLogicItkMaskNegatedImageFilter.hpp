#pragma once

#include "gmLogicItkBinaryFunctorImageFilter.hpp"
#include "gmLogicItkUtil.hpp"

#include <itkMaskNegatedImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class MaskNegatedImageFilter : public BinaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto inputImages = "input images";
                    static constexpr auto inputMasks = "input masks";
                    static constexpr auto maskingValue = "masking value";
                    static constexpr auto outsideValue = "outside value";
                    static constexpr auto output = "output";
                };
                
                static Register<MaskNegatedImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                MaskNegatedImageFilter() : BinaryFunctorImageFilter("MaskNegatedImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->addParamGroup("MaskNegatedImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::inputImages, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::inputMasks, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::maskingValue, {"r", "g", "b", "a"}, 0));
                    this->add(new Param::Vector(ID::outsideValue, {"r", "g", "b", "a"}, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::MaskNegatedImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetMaskImage(Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::inputMasks)->getImage()));
                    
                    filter->SetMaskingValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::maskingValue)->getValues()));
                    filter->SetOutsideValue(Util::VectorToPixel<typename ImageType::PixelType>(this->getParam<Param::Vector>(ID::outsideValue)->getValues()));
                    
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