#pragma once

#include <itkImage.h>

namespace gm
{
    namespace Image
    {
        template <class TPixelType, unsigned int TDimension>
        struct Type
        {
            static constexpr unsigned int dimension = TDimension;
            using pixel = TPixelType;
            using itk_image_t = itk::Image<typename TPixelType::itk_pixel_t, TDimension>;
        };
    }
}