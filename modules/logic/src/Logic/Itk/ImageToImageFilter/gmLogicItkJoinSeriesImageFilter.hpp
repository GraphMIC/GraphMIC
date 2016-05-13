#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkJoinSeriesImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class JoinSeriesImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto origin = "origin";
                    static constexpr auto spacing = "spacing";
                    static constexpr auto output = "output";
                };
                
                static Register<JoinSeriesImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                JoinSeriesImageFilter() : ImageToImageFilter("JoinSeriesImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("JoinSeriesImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::origin, 0));
                    this->add(new Param::Number(ID::spacing, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using OutputType    = itk::Image<typename ImageType::PixelType, TImage::dimension + 1>;
                    using FilterType    = itk::JoinSeriesImageFilter<ImageType, OutputType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);

                    auto origin = this->getParam<Param::Number>(ID::origin)->getValue();
                    auto spacing = this->getParam<Param::Number>(ID::spacing)->getValue();

                    auto i = 0;

                    filter->SetOrigin(origin);
                    filter->SetSpacing(spacing);

                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(i++, Image::ToItk<ImageType>(it.image()));
                    }

                    filter->Update();
                    output->addImage(Image::FromItk<OutputType>(filter->GetOutput()));
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