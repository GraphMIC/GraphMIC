#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkBinaryGrindPeakImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryGrindPeakImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto foregroundValue = "foreground value";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto fullyConnected = "fully connected";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryGrindPeakImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryGrindPeakImageFilter() : ImageToImageFilter("BinaryGrindPeakImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryGrindPeakImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::foregroundValue, 1));
                    this->add(new Param::Number(ID::backgroundValue, 0));
                    this->add(new Param::Bool(ID::fullyConnected, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryGrindPeakImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetForegroundValue(this->getParam<Param::Number>(ID::foregroundValue)->getValue());
                    filter->SetBackgroundValue(this->getParam<Param::Number>(ID::backgroundValue)->getValue());
                    filter->SetFullyConnected(this->getParam<Param::Bool>(ID::fullyConnected)->getValue());
                    
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