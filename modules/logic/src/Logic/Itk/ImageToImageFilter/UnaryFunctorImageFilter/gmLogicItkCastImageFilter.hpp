#pragma once

#include "gmLogicItkUnaryFunctorImageFilter.hpp"

#include <itkCastImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class CastImageFilter : public UnaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto type = "type";
                    static constexpr auto output = "output";
                };
                
                static Register<CastImageFilter> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;
                
                CastImageFilter() : UnaryFunctorImageFilter("CastImageFilter")
                {
                    log_trace(Log::New);
                    
                    this->addParamGroup("CastImageFilter");
                    
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::type, {"unsigned char", "unsigned short", "unsigned int", "char", "short", "int", "float", "double"}));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TInputImage, class TOutputImage>
                auto processCast() -> void
                {
                    using FilterType = itk::CastImageFilter<TInputImage, TOutputImage>;
                    
                    auto filter = FilterType::New();
                    auto output = this->getOutput<Data::Image>(ID::output);
                    
                    applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput(Image::ToItk<TInputImage>(it.image()));
                        filter->Update();
                        output->addImage(Image::FromItk<TOutputImage>(filter->GetOutput()));
                    }
                }
                
                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Scalar, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using ImageType = typename TImage::itk_image_t;
                    
                    auto index = this->getParam<Param::Option>(ID::type)->getIndex();
                    
                    switch (index)
                    {
                        case 0: processCast<ImageType, itk::Image<unsigned char, TImage::dimension>>(); break;
                        case 1: processCast<ImageType, itk::Image<unsigned short, TImage::dimension>>(); break;
                        case 2: processCast<ImageType, itk::Image<unsigned int, TImage::dimension>>(); break;
                        case 3: processCast<ImageType, itk::Image<char, TImage::dimension>>(); break;
                        case 4: processCast<ImageType, itk::Image<short, TImage::dimension>>(); break;
                        case 5: processCast<ImageType, itk::Image<int, TImage::dimension>>(); break;
                        case 6: processCast<ImageType, itk::Image<float, TImage::dimension>>(); break;
                        case 7: processCast<ImageType, itk::Image<double, TImage::dimension>>(); break;
                        default: processCast<ImageType, itk::Image<double, TImage::dimension>>(); break;
                    }
                }
                            
                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Rgb, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using ImageType = typename TImage::itk_image_t;
                    
                    auto index = this->getParam<Param::Option>(ID::type)->getIndex();
                    
                    switch (index)
                    {
                        case 0: processCast<ImageType, itk::Image<itk::RGBPixel<unsigned char>, TImage::dimension>>(); break;
                        case 1: processCast<ImageType, itk::Image<itk::RGBPixel<unsigned short>, TImage::dimension>>(); break;
                        case 2: processCast<ImageType, itk::Image<itk::RGBPixel<unsigned int>, TImage::dimension>>(); break;
                        case 3: processCast<ImageType, itk::Image<itk::RGBPixel<char>, TImage::dimension>>(); break;
                        case 4: processCast<ImageType, itk::Image<itk::RGBPixel<short>, TImage::dimension>>(); break;
                        case 5: processCast<ImageType, itk::Image<itk::RGBPixel<int>, TImage::dimension>>(); break;
                        case 6: processCast<ImageType, itk::Image<itk::RGBPixel<float>, TImage::dimension>>(); break;
                        case 7: processCast<ImageType, itk::Image<itk::RGBPixel<double>, TImage::dimension>>(); break;
                        default: processCast<ImageType, itk::Image<itk::RGBPixel<double>, TImage::dimension>>(); break;
                    }
                }
                            
                template <class TImage,
                typename std::enable_if<TImage::pixel::id == Image::Pixel::ID::Rgba, std::size_t >::type = 0 >
                auto process() -> void
                {
                    using ImageType = typename TImage::itk_image_t;
                                
                    auto index = this->getParam<Param::Option>(ID::type)->getIndex();
                                
                    switch (index)
                    {
                        case 0: processCast<ImageType, itk::Image<itk::RGBAPixel<unsigned char>, TImage::dimension>>(); break;
                        case 1: processCast<ImageType, itk::Image<itk::RGBAPixel<unsigned short>, TImage::dimension>>(); break;
                        case 2: processCast<ImageType, itk::Image<itk::RGBAPixel<unsigned int>, TImage::dimension>>(); break;
                        case 3: processCast<ImageType, itk::Image<itk::RGBAPixel<char>, TImage::dimension>>(); break;
                        case 4: processCast<ImageType, itk::Image<itk::RGBAPixel<short>, TImage::dimension>>(); break;
                        case 5: processCast<ImageType, itk::Image<itk::RGBAPixel<int>, TImage::dimension>>(); break;
                        case 6: processCast<ImageType, itk::Image<itk::RGBAPixel<float>, TImage::dimension>>(); break;
                        case 7: processCast<ImageType, itk::Image<itk::RGBAPixel<double>, TImage::dimension>>(); break;
                        default: processCast<ImageType, itk::Image<itk::RGBAPixel<double>, TImage::dimension>>(); break;
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