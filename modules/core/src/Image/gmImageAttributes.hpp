#pragma once

#include "gmCoreExport.hpp"

#include <mitkImage.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>

namespace gm
{
    namespace Image
    {
        namespace Pixel
        {
            enum class ID
            {
                Scalar,
                Rgb,
                Rgba
            };

            template <class TComponent>
            struct Scalar
            {
                using component_t = TComponent;
                using itk_pixel_t = TComponent;
                static constexpr ID id = ID::Scalar;
            };

            template <class TComponent>
            struct Rgb
            {
                using component_t = TComponent;
                using itk_pixel_t = itk::RGBPixel<TComponent>;
                static constexpr ID id = ID::Rgb;
            };

            template <class TComponent>
            struct Rgba
            {
                using component_t = TComponent;
                using itk_pixel_t = itk::RGBAPixel<TComponent>;
                static constexpr ID id = ID::Rgba;
            };
        }

        namespace Component
        {
            enum class ID
            {
                UChar,
                UShort,
                UInt,
                Char,
                Short,
                Int,
                Float,
                Double
            };
        }

        class GM_CORE_EXPORT Attributes
        {
        private:
            unsigned int m_dimension;
            Pixel::ID m_pixelID;
            Component::ID m_componentID;
        public:
            Attributes(mitk::Image::Pointer);
            Attributes(const unsigned int, Pixel::ID, Component::ID);
            auto getDimension() -> const unsigned int;
            auto getPixelID() -> const Pixel::ID;
            auto getComponentID() -> const Component::ID;
        };
    }
}
