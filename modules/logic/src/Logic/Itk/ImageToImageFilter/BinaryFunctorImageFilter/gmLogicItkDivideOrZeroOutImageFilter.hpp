#pragma once

#include "gmLogicItkBinaryFunctorImageFilter.hpp"

#include <itkDivideOrZeroOutImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class DivideOrZeroOutImageFilter : public BinaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto threshold = "threshold";
                    static constexpr auto constant = "constant";
                    static constexpr auto output = "output";
                };
                
                static Register<DivideOrZeroOutImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                DivideOrZeroOutImageFilter() : BinaryFunctorImageFilter("DivideOrZeroOutImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->addParamGroup("DivideOrZeroOutImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::threshold, 1e-5));
                    this->add(new Param::Number(ID::constant, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    throw new std::runtime_error("unsupported"); // to avoid itk runtime 0-division

                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::DivideOrZeroOutImageFilter<ImageType, ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    BinaryFunctorImageFilter::applyParameters<FilterType>(filter);
                    
                    filter->SetThreshold(this->getParam<Param::Number>(ID::threshold)->getValue());
                    filter->SetConstant(this->getParam<Param::Number>(ID::constant)->getValue());
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput1(Image::ToItk<ImageType>(it.image(0)));
                        filter->SetInput2(Image::ToItk<ImageType>(it.image(1)));
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
