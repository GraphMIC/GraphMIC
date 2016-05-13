#pragma once

#include <itkPixelTraits.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            namespace Util
            {
                template <class TPixel,
                typename std::enable_if<(itk::PixelTraits<TPixel>::Dimension == 1), std::size_t>::type = 0 >
                auto VectorToPixel(std::array<double, 4> color) -> TPixel
                {
                    TPixel pixel = color[0];
                    
                    return pixel;
                }
                
                template <class TPixel,
                typename std::enable_if<(itk::PixelTraits<TPixel>::Dimension > 1), std::size_t>::type = 0 >
                auto VectorToPixel(std::array<double, 4> color) -> TPixel
                {
                    TPixel pixel;
                    
                    for (auto i = 0; i < itk::PixelTraits<TPixel>::Dimension; ++i)
                    {
                        pixel[i] = static_cast<typename itk::PixelTraits<TPixel>::ValueType>(color[i]);
                    }
                    
                    return pixel;
                }
            }
        }
    }
}