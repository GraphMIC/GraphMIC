#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkCheckerBoardImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class CheckerBoardImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto checkerPattern = "checker pattern";
                    static constexpr auto output = "output";
                };
                
                static Register<CheckerBoardImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                CheckerBoardImageFilter() : ImageToImageFilter("CheckerBoardImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("CheckerBoardImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Vector(ID::checkerPattern, {"x", "y", "z"}, 4));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::CheckerBoardImageFilter<ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    auto pattern_vec    = this->getParam<Param::Vector>(ID::checkerPattern)->getValues();
                    
                    ImageToImageFilter::applyParameters<FilterType>(filter);
                    
                    typename FilterType::PatternArrayType pattern;
                    
                    for (auto i = 0; i < TImage::dimension; ++i)
                    {
                        pattern[i] = pattern_vec[i];
                    }
                    
                    filter->SetCheckerPattern(pattern);
                    
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
