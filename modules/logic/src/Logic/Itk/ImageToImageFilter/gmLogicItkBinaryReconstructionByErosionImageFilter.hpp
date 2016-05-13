#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkBinaryReconstructionByErosionImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryReconstructionByErosionImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto mask = "mask";
                    static constexpr auto marker = "marker";
                    static constexpr auto foregroundValue = "foreground value";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto fullyConnected = "fully connected";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryReconstructionByErosionImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryReconstructionByErosionImageFilter() : ImageToImageFilter("BinaryReconstructionByErosionImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryReconstructionByErosionImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::marker, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::mask, Access::MakeConstraints(), Data::Optional));
                    this->add(new Param::Number(ID::foregroundValue, 1));
                    this->add(new Param::Number(ID::backgroundValue, 0));
                    this->add(new Param::Bool(ID::fullyConnected, false));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryReconstructionByErosionImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto mask           = Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::mask)->getImage());
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetForegroundValue(this->getParam<Param::Number>(ID::foregroundValue)->getValue());
                    filter->SetBackgroundValue(this->getParam<Param::Number>(ID::backgroundValue)->getValue());
                    filter->SetFullyConnected(this->getParam<Param::Bool>(ID::fullyConnected)->getValue());
                    filter->SetMarkerImage(Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::marker)->getImage()));

                    if (mask)
                    {
                        filter->SetMaskImage(mask);
                    }
                    
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