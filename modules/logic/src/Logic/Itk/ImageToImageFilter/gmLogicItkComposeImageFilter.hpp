#pragma once

#include "gmLogicItkImageToImageFilter.hpp"
#include "gmImageConvert.hpp"

#include <itkComposeImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class ComposeImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto inputR = "input R";
                    static constexpr auto inputG = "input G";
                    static constexpr auto inputB = "input B";
                    static constexpr auto inputA = "input A";
                    static constexpr auto output = "output";
                };

                static Register<ComposeImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                using Output = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ComposeImageFilter() : ImageToImageFilter("ComposeImageFilter")
                {
                    log_trace(Log::New);

                    this->addParamGroup("ComposeImageFilter");

                    this->add(new Slot::Input<Data::Image>(ID::inputR, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::inputG, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::inputB, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::inputA, Access::MakeConstraints(), Data::Optional));
                    this->add(new Slot::Output<Data::Image>(ID::output, Output::MakeConstraints()));
                }

                template <class TImage>
                auto process() -> void
                {
                    auto inputA = this->getInput<Data::Image>(ID::inputA);
                    auto outputA = inputA->getOutput();
                    auto output = this->getOutput<Data::Image>(ID::output);

                    using InputType = typename TImage::itk_image_t;

                    if (outputA && outputA->getDataCount() > 0)
                    {
                        using RGBAType = itk::Image<itk::RGBAPixel<typename TImage::pixel::component_t>, TImage::dimension>;
                        using RGBAFilterType = itk::ComposeImageFilter<typename TImage::itk_image_t, RGBAType>;

                        auto filter = RGBAFilterType::New();

                        for (auto it : this->inputIterator())
                        {
                            filter->SetInput(0, Image::ToItk<InputType>(it.image(0)));
                            filter->SetInput(1, Image::ToItk<InputType>(it.image(1)));
                            filter->SetInput(2, Image::ToItk<InputType>(it.image(2)));
                            filter->SetInput(3, Image::ToItk<InputType>(it.image(3)));
                            filter->Update();

                            output->addImage(Image::FromItk<RGBAType>(filter->GetOutput()));
                        }
                    }
                    else
                    {
                        using RGBType = itk::Image<itk::RGBPixel<typename TImage::pixel::component_t>, TImage::dimension>;
                        using RGBFilterType = itk::ComposeImageFilter<typename TImage::itk_image_t, RGBType>;

                        auto filter = RGBFilterType::New();

                        for (auto it : this->inputIterator())
                        {
                            filter->SetInput1(Image::ToItk<InputType>(it.image(0)));
                            filter->SetInput2(Image::ToItk<InputType>(it.image(1)));
                            filter->SetInput3(Image::ToItk<InputType>(it.image(2)));
                            filter->Update();

                            output->addImage(Image::FromItk<RGBType>(filter->GetOutput()));
                        }
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