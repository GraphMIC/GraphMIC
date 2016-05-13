#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkHoughTransform2DCirclesImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class HoughTransform2DCirclesImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto numberOfCircles = "number of circles";
                    static constexpr auto minimumRadius = "minimum radius";
                    static constexpr auto maximumRadius = "maximum radius";
                    static constexpr auto sigmaGradient = "sigma gradient";
                    static constexpr auto discRadiusRatio = "disc radius ratio";
                    static constexpr auto sweepAngle = "sweep angle";
                    static constexpr auto threshold = "threshold";
                    static constexpr auto variance = "variance";
                    static constexpr auto outputImages = "images";
                };
                
                static Register<HoughTransform2DCirclesImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                HoughTransform2DCirclesImageFilter() : ImageToImageFilter("HoughTransform2DCirclesImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("HoughTransform2DCirclesImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::numberOfCircles, 1));
                    this->add(new Param::Number(ID::minimumRadius, 0));
                    this->add(new Param::Number(ID::maximumRadius, 10));
                    this->add(new Param::Number(ID::sigmaGradient, 1));
                    this->add(new Param::Number(ID::discRadiusRatio, 1));
                    this->add(new Param::Number(ID::sweepAngle, 0));
                    this->add(new Param::Number(ID::threshold, 0));
                    this->add(new Param::Number(ID::variance, 10));
                    this->add(new Slot::Output<Data::Image>(ID::outputImages, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::HoughTransform2DCirclesImageFilter<typename TImage::pixel::component_t, float>;
                    
                    auto filter         = FilterType::New();
                    auto outputImages   = this->getOutput<Data::Image>(ID::outputImages);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetVariance(this->getParam<Param::Number>(ID::variance)->getValue());
                    filter->SetThreshold(this->getParam<Param::Number>(ID::threshold)->getValue());
                    filter->SetSweepAngle(this->getParam<Param::Number>(ID::sweepAngle)->getValue());
                    filter->SetMinimumRadius(this->getParam<Param::Number>(ID::minimumRadius)->getValue());
                    filter->SetMaximumRadius(this->getParam<Param::Number>(ID::maximumRadius)->getValue());
                    filter->SetDiscRadiusRatio(this->getParam<Param::Number>(ID::discRadiusRatio)->getValue());
                    filter->SetNumberOfCircles(this->getParam<Param::Number>(ID::numberOfCircles)->getValue());
                    
                    for (auto it : this->inputIterator())
                    {
                        /*
                        filter->SetInput(Image::ToItk<ImageType>(it.image()));
                        filter->Update();

                        outputImages->addImage(Image::FromItk<itk::Image<float, 2>>(filter->GetOutput()));
*/
                        /*
                        auto circles = filter->GetCircles();

                        for (auto circle : circles)
                        {
                            auto point = circle->GetObjectToParentTransform()->GetOffset();
                            output_points->addPoint(point[0], point[1]);
                        }
                        */
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