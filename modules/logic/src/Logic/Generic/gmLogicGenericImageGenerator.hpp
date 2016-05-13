#pragma once

#include "gmLogicGenericBase.hpp"
#include "gmNodeObject.hpp"

#include "gmLogicEnable.hpp"
#include "gmLogicInvoke.hpp"

#include <random>

#include <itkImageRegionIterator.h>
#include <itkComposeImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Generic
        {
            class ImageGenerator : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto size = "size";
                    static constexpr auto min = "min";
                    static constexpr auto max = "max";
                    static constexpr auto dimension = "dimension";
                    static constexpr auto pixelType = "pixel type";
                    static constexpr auto componentType = "component type";
                    static constexpr auto output = "output";
                };

                static Register<ImageGenerator> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ImageGenerator() : Base("ImageGenerator")
                {
                    log_trace(Log::New, this);

                    this->setIsDataSource(true);
                    this->setUseTimer(true);
                    this->setThreaded(true);
                    this->setRunnable(true);
                    this->setForceExecution(true);

                    this->add(new Param::Option(ID::dimension, {
                        "2D",
                        "3D"
                    }));

                    this->add(new Param::Option(ID::pixelType, {
                        "Scalar",
                        "RGB",
                        "RGBA"
                    }));

                    this->add(new Param::Option(ID::componentType, {
                        "UChar",
                        "UShort",
                        "UInt",
                        "Char",
                        "Short",
                        "Int",
                        "Float",
                        "Double"
                    }));

                    this->add(new Param::Number(ID::size, 128, 0, 100000));
                    this->add(new Param::Number(ID::min, 0, 0, 100000));
                    this->add(new Param::Number(ID::max, 255, 0, 100000));

                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                template <class TImage, unsigned int dimension>
                auto generateImageData(int imageSize, double min, double max) -> typename TImage::Pointer
                {
                    std::random_device rd;
                    std::mt19937 generator(rd());

                    itk::Size<dimension> size;
                    itk::Index<dimension> start;

                    start.Fill(0);
                    size.Fill(imageSize);

                    typedef itk::ImageRegionIterator<TImage> IteratorType;
                    typename TImage::Pointer image = TImage::New();
                    typename TImage::RegionType region(start, size);

                    image->SetRegions(region);
                    image->Allocate();

                    IteratorType it(image, image->GetRequestedRegion());

                    std::uniform_real_distribution<double> distribution(min, max);

                    for (it.GoToBegin(); !it.IsAtEnd(); ++it)
                    {
                        it.Set(distribution(generator));
                    }

                    return image;
                }

                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Scalar, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using ImageType = typename TImage::itk_image_t;

                    auto size   = this->getParam<Param::Number>(ID::size)->getValue();
                    auto min    = this->getParam<Param::Number>(ID::min)->getValue();
                    auto max    = this->getParam<Param::Number>(ID::max)->getValue();

                    auto output = this->getOutput<Data::Image>(ID::output);
                    output->addImage(Image::FromItk<ImageType>(generateImageData<ImageType, TImage::dimension>(size, min, max)));
                }

                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Rgb, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using RgbImageType = typename TImage::itk_image_t;
                    using SingleChannelImageType = itk::Image<typename TImage::pixel::component_t, TImage::dimension>;
                    using FilterType = itk::ComposeImageFilter<SingleChannelImageType, RgbImageType>;

                    auto size   = this->getParam<Param::Number>(ID::size)->getValue();
                    auto min    = this->getParam<Param::Number>(ID::min)->getValue();
                    auto max    = this->getParam<Param::Number>(ID::max)->getValue();
                    auto output = this->getOutput<Data::Image>(ID::output);

                    auto imageR = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);
                    auto imageG = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);
                    auto imageB = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);

                    auto filter = FilterType::New();

                    filter->SetInput(0, imageR);
                    filter->SetInput(1, imageG);
                    filter->SetInput(2, imageB);

                    filter->Update();

                    output->addImage(Image::FromItk<RgbImageType>(filter->GetOutput()));
                }

                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Rgba, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using RgbaImageType = typename TImage::itk_image_t;
                    using SingleChannelImageType = itk::Image<typename TImage::pixel::component_t, TImage::dimension>;
                    using FilterType = itk::ComposeImageFilter<SingleChannelImageType, RgbaImageType>;

                    auto size   = this->getParam<Param::Number>(ID::size)->getValue();
                    auto min    = this->getParam<Param::Number>(ID::min)->getValue();
                    auto max    = this->getParam<Param::Number>(ID::max)->getValue();
                    auto output = this->getOutput<Data::Image>(ID::output);

                    auto imageR = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);
                    auto imageG = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);
                    auto imageB = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);
                    auto imageA = generateImageData<SingleChannelImageType, TImage::dimension>(size, min, max);

                    auto filter = FilterType::New();

                    filter->SetInput(0, imageR);
                    filter->SetInput(1, imageG);
                    filter->SetInput(2, imageB);
                    filter->SetInput(3, imageA);

                    filter->Update();
                    
                    output->addImage(Image::FromItk<RgbaImageType>(filter->GetOutput()));
                }

                auto run() -> void override
                {
                    log_trace(Log::Func);

                    auto dimension      = 2;
                    auto pixelID        = Image::Pixel::ID::Scalar;
                    auto componentID    = Image::Component::ID::UChar;

                    auto dimensionIndex = this->getParam<Param::Option>(ID::dimension)->getIndex();
                    auto pixelIndex = this->getParam<Param::Option>(ID::pixelType)->getIndex();
                    auto componentIndex = this->getParam<Param::Option>(ID::componentType)->getIndex();

                    switch (dimensionIndex)
                    {
                        case 0: dimension = 2; break;
                        case 1: dimension = 3; break;

                        default: dimension = 2; break;
                    }

                    switch (pixelIndex)
                    {
                        case 0: pixelID = Image::Pixel::ID::Scalar; break;
                        case 1: pixelID = Image::Pixel::ID::Rgb; break;
                        case 2: pixelID = Image::Pixel::ID::Rgba; break;

                        default: pixelID = Image::Pixel::ID::Scalar; break;
                    }

                    switch (componentIndex)
                    {
                        case 0: componentID = Image::Component::ID::UChar; break;
                        case 1: componentID = Image::Component::ID::UShort; break;
                        case 2: componentID = Image::Component::ID::UInt; break;
                        case 3: componentID = Image::Component::ID::Char; break;
                        case 4: componentID = Image::Component::ID::Short; break;
                        case 5: componentID = Image::Component::ID::Int; break;
                        case 6: componentID = Image::Component::ID::Float; break;
                        case 7: componentID = Image::Component::ID::Double; break;

                        default: componentID = Image::Component::ID::UChar; break;
                    }

                    Invoke(this, dimension, pixelID, componentID);
                }

                ~ImageGenerator()
                {
                    log_trace(Log::Del, this);
                }
            };
        }
    }
}