#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkBilateralImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BilateralImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto radius = "radius";
                    static constexpr auto domainSigma = "domain sigma";
                    static constexpr auto rangeSigma = "range sigma";
                    static constexpr auto domainMu = "domain mu";
                    static constexpr auto output = "output";
                    static constexpr auto filterDimensionality = "filter dimensionality";
                    static constexpr auto automaticKernelSize = "automatic kernel size";
                    static constexpr auto numberRangeGaussianSamples = "number of range gaussian samples";
                };
                
                static Register<BilateralImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BilateralImageFilter() : ImageToImageFilter("BilateralImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->addParamGroup("BilateralImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::radius, 1));
                    this->add(new Param::Number(ID::domainSigma, 4));
                    this->add(new Param::Number(ID::rangeSigma, 50));
                    this->add(new Param::Number(ID::domainMu, 2.5));
                    this->add(new Param::Number(ID::numberRangeGaussianSamples, 100));
                    this->add(new Param::Number(ID::filterDimensionality, 2));
                    this->add(new Param::Bool(ID::automaticKernelSize, true));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BilateralImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetRadius(this->getParam<Param::Number>(ID::radius)->getValue());
                    filter->SetDomainSigma(this->getParam<Param::Number>(ID::domainSigma)->getValue());
                    filter->SetRangeSigma(this->getParam<Param::Number>(ID::rangeSigma)->getValue());
                    filter->SetDomainMu(this->getParam<Param::Number>(ID::domainMu)->getValue());
                    filter->SetNumberOfRangeGaussianSamples(this->getParam<Param::Number>(ID::numberRangeGaussianSamples)->getValue());
                    filter->SetFilterDimensionality(this->getParam<Param::Number>(ID::filterDimensionality)->getValue());
                    filter->SetAutomaticKernelSize(this->getParam<Param::Bool>(ID::automaticKernelSize)->getValue());
                    
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