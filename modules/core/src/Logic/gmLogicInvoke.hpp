#pragma once

#include "gmImageAttributes.hpp"
#include "gmDataImage.hpp"
#include "gmImageType.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Logic
    {
        template <class TLogic, class TImage,
        typename std::enable_if<(!TLogic::Access::template accepts<TImage>()), std::size_t>::type = 0 >
        auto Invoke(TLogic* logic) -> void
        {
             throw new std::runtime_error("unsupported image properties");
        }

        template <class TLogic, class TImage,
        typename std::enable_if<(TLogic::Access::template accepts<TImage>()), std::size_t>::type = 0 >
        auto Invoke(TLogic* logic) -> void
        {
            logic->template process<TImage>();
        }

        template <class TLogic>
        auto Invoke(TLogic* logic, const unsigned int dimension, Image::Pixel::ID pixelID, Image::Component::ID componentID) -> void
        {
            switch (dimension)
            {
                case 2:
                {
                    switch (pixelID)
                    {
                        case Image::Pixel::ID::Scalar:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned char>, 2>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned short>, 2>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned int>, 2>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Scalar<char>, 2>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<short>, 2>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Scalar<int>, 2>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<float>, 2>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Scalar<double>, 2>>(logic); break;
                            }
                            break;
                        }

                        case Image::Pixel::ID::Rgb:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned char>, 2>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned short>, 2>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned int>, 2>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Rgb<char>, 2>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<short>, 2>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Rgb<int>, 2>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<float>, 2>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Rgb<double>, 2>>(logic); break;
                            }
                            break;
                        }

                        case Image::Pixel::ID::Rgba:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned char>, 2>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned short>, 2>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned int>, 2>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Rgba<char>, 2>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<short>, 2>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Rgba<int>, 2>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<float>, 2>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Rgba<double>, 2>>(logic); break;
                            }
                            break;
                        }
                    }
                    break;
                }

                case 3:
                {
                    switch (pixelID)
                    {
                        case Image::Pixel::ID::Scalar:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned char>, 3>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned short>, 3>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Scalar<unsigned int>, 3>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Scalar<char>, 3>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<short>, 3>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Scalar<int>, 3>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Scalar<float>, 3>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Scalar<double>, 3>>(logic); break;
                            }
                            break;
                        }

                        case Image::Pixel::ID::Rgb:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned char>, 3>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned short>, 3>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Rgb<unsigned int>, 3>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Rgb<char>, 3>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<short>, 3>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Rgb<int>, 3>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Rgb<float>, 3>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Rgb<double>, 3>>(logic); break;
                            }
                            break;
                        }

                        case Image::Pixel::ID::Rgba:
                        {
                            switch (componentID)
                            {
                                case Image::Component::ID::UChar:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned char>, 3>>(logic); break;
                                case Image::Component::ID::UShort:  Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned short>, 3>>(logic); break;
                                case Image::Component::ID::UInt:    Invoke<TLogic, Image::Type<Image::Pixel::Rgba<unsigned int>, 3>>(logic); break;
                                case Image::Component::ID::Char:    Invoke<TLogic, Image::Type<Image::Pixel::Rgba<char>, 3>>(logic); break;
                                case Image::Component::ID::Short:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<short>, 3>>(logic); break;
                                case Image::Component::ID::Int:     Invoke<TLogic, Image::Type<Image::Pixel::Rgba<int>, 3>>(logic); break;
                                case Image::Component::ID::Float:   Invoke<TLogic, Image::Type<Image::Pixel::Rgba<float>, 3>>(logic); break;
                                case Image::Component::ID::Double:  Invoke<TLogic, Image::Type<Image::Pixel::Rgba<double>, 3>>(logic); break;
                            }
                            break;
                        }
                    }
                    break;
                }

                default:
                {
                    // exc: unsupported image dimension
                    break;
                }
            }
        }

        template <class TLogic>
        auto Invoke(TLogic* logic) -> void
        {
            auto image = logic->template invokable();
            
            if (!image)
            {
                throw new std::runtime_error("no image found to invoke logic");
            }

            auto attributes = image->getAttributes();

            Invoke<TLogic>(logic, attributes->getDimension(), attributes->getPixelID(), attributes->getComponentID());
        }
    }
}