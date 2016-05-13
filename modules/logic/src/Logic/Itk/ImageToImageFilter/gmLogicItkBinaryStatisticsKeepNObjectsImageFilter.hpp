#pragma once

#include "gmLogicItkImageToImageFilter.hpp"

#include <itkBinaryStatisticsKeepNObjectsImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class BinaryStatisticsKeepNObjectsImageFilter : public ImageToImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto featureImage = "feature image";
                    static constexpr auto numberOfObjects = "number of objects";
                    static constexpr auto foregroundValue = "foreground value";
                    static constexpr auto backgroundValue = "background value";
                    static constexpr auto fullyConnected = "fully connected";
                    static constexpr auto reverseOrdering = "reverse ordering";
                    static constexpr auto attribute = "attribute";
                    static constexpr auto output = "output";
                };
                
                static Register<BinaryStatisticsKeepNObjectsImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                BinaryStatisticsKeepNObjectsImageFilter() : ImageToImageFilter("BinaryStatisticsKeepNObjectsImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("BinaryStatisticsKeepNObjectsImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::featureImage, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::numberOfObjects, 0));
                    this->add(new Param::Number(ID::foregroundValue, 1));
                    this->add(new Param::Number(ID::backgroundValue, 0));
                    this->add(new Param::Bool(ID::fullyConnected, false));
                    this->add(new Param::Bool(ID::reverseOrdering, false));
                    this->add(new Param::Option(ID::attribute, {
                        "number of pixels",
                        "physical size",
                        "centroid",
                        "bounding box",
                        "number of pixels on border",
                        "perimeter on border",
                        "feret diameter",
                        "principal moments",
                        "principal axes",
                        "elongation",
                        "perimeter",
                        "roundness",
                        "equivalent spherical radius",
                        "equivalent spherical perimeter",
                        "equivalent ellipsoid diameter",
                        "flatness",
                        "perimeter on border ratio"}
                    ));
                    
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::BinaryStatisticsKeepNObjectsImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    filter->SetNumberOfObjects(this->getParam<Param::Number>(ID::numberOfObjects)->getValue());
                    filter->SetForegroundValue(this->getParam<Param::Number>(ID::foregroundValue)->getValue());
                    filter->SetBackgroundValue(this->getParam<Param::Number>(ID::backgroundValue)->getValue());
                    filter->SetFullyConnected(this->getParam<Param::Bool>(ID::fullyConnected)->getValue());
                    filter->SetReverseOrdering(this->getParam<Param::Bool>(ID::reverseOrdering)->getValue());
                    filter->SetFeatureImage(Image::ToItk<ImageType>(this->getInput<Data::Image>(ID::featureImage)->getImage()));
                    
                    typename FilterType::AttributeType attr;
                    
                    switch (this->getParam<Param::Option>(ID::attribute)->getIndex())
                    {
                        case 0: attr = FilterType::LabelObjectType::NUMBER_OF_PIXELS; break;
                        case 1: attr = FilterType::LabelObjectType::PHYSICAL_SIZE; break;
                        case 2: attr = FilterType::LabelObjectType::CENTROID; break;
                        case 3: attr = FilterType::LabelObjectType::BOUNDING_BOX; break;
                        case 4: attr = FilterType::LabelObjectType::NUMBER_OF_PIXELS_ON_BORDER; break;
                        case 5: attr = FilterType::LabelObjectType::PERIMETER_ON_BORDER; break;
                        case 6: attr = FilterType::LabelObjectType::FERET_DIAMETER; break;
                        case 7: attr = FilterType::LabelObjectType::PRINCIPAL_MOMENTS; break;
                        case 8: attr = FilterType::LabelObjectType::PRINCIPAL_AXES; break;
                        case 9: attr = FilterType::LabelObjectType::ELONGATION; break;
                        case 10: attr = FilterType::LabelObjectType::PERIMETER; break;
                        case 11: attr = FilterType::LabelObjectType::ROUNDNESS; break;
                        case 12: attr = FilterType::LabelObjectType::EQUIVALENT_SPHERICAL_RADIUS; break;
                        case 13: attr = FilterType::LabelObjectType::EQUIVALENT_SPHERICAL_PERIMETER; break;
                        case 14: attr = FilterType::LabelObjectType::EQUIVALENT_ELLIPSOID_DIAMETER; break;
                        case 15: attr = FilterType::LabelObjectType::FLATNESS; break;
                        case 16: attr = FilterType::LabelObjectType::PERIMETER_ON_BORDER_RATIO; break;
                            
                        default: attr = FilterType::LabelObjectType::NUMBER_OF_PIXELS;
                    }
                    
                    filter->SetAttribute(attr);
                    
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