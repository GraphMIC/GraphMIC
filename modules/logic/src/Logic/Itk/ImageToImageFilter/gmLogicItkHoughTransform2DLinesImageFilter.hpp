#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkHoughTransform2DLinesImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class HoughTransform2DLinesImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto numberOfLines = "number of lines";
                    static constexpr auto threshold = "threshold";
                    static constexpr auto angleResolution = "angle resolution";
                    static constexpr auto discRadius = "disc radius";
                    static constexpr auto variance = "variance";
                    static constexpr auto outputImages = "images";
                    static constexpr auto outputPointset = "point set";
                };
                
                static Register<HoughTransform2DLinesImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<float, double>
                >;

                HoughTransform2DLinesImageFilter() : ImageToImageFilter("HoughTransform2DLinesImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("HoughTransform2DLinesImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::numberOfLines, 1));
                    this->add(new Param::Number(ID::threshold, 0));
                    this->add(new Param::Number(ID::angleResolution, 500));
                    this->add(new Param::Number(ID::discRadius, 1));
                    this->add(new Param::Number(ID::variance, 5));
                    this->add(new Slot::Output<Data::Image>(ID::outputImages, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    /*
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::HoughTransform2DLinesImageFilter<typename TImage::pixel::component_t, float>;
                    
                    auto filter         = FilterType::New();
                    auto outputImages   = this->getOutput<Data::Image>(ID::outputImages);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetVariance(this->getParam<Param::Number>(ID::variance)->getValue());
                    filter->SetThreshold(this->getParam<Param::Number>(ID::threshold)->getValue());
                    filter->SetDiscRadius(this->getParam<Param::Number>(ID::discRadius)->getValue());
                    filter->SetNumberOfLines(this->getParam<Param::Number>(ID::numberOfLines)->getValue());
                    filter->SetAngleResolution(this->getParam<Param::Number>(ID::angleResolution)->getValue());
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(Image::ToItk<ImageType>(it.image()));
                        filter->Update();

                        outputImages->addImage(Image::FromItk<itk::Image<float, 2>>(filter->GetOutput()));
*/
                        /*
                        auto lines = filter->GetLines();
                        
                        for (auto line : lines)
                        {
                            for (auto point : line->GetPoints())
                            {
                                auto pos = point.GetPosition();
                                output_points->addPoint(pos[0], pos[1]);
                            }
                        }*/
                  //  }
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