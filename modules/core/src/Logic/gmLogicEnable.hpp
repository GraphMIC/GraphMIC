#pragma once

#include <bitset>

#include "gmCoreExport.hpp"
#include "gmImageAttributes.hpp"
#include "gmSlotConstraints.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Enable
        {
            namespace Bitset
            {
                template <unsigned int TDimension>
                struct GM_CORE_EXPORT ForDimension
                {
                    static const std::bitset<4> bitset;
                };

                template <class TComponent>
                struct GM_CORE_EXPORT ForComponent
                {
                    static const std::bitset<8> bitset;
                };
            }

            template <unsigned int...Dims>
            struct Dimension
            {
                static constexpr auto MakeBitset() -> std::bitset<4>
                {
                    return std::bitset<4>();
                }

                static constexpr auto contains(const unsigned int dimension) -> bool
                {
                    return false;
                }
            };

            template <unsigned int A, unsigned int...X>
            struct Dimension<A,X...>
            {
                static constexpr auto MakeBitset() -> std::bitset<4>
                {
                    return Bitset::ForDimension<A>::bitset | Dimension<X...>::MakeBitset();
                }

                static constexpr auto contains(const unsigned int dimension) -> bool
                {
                    return (A == dimension || Dimension<X...>::contains(dimension));
                }
            };

            template <class...TComponents>
            struct Scalar
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return std::bitset<8>();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return false;
                }
            };

            template <class A, class...X>
            struct Scalar<A,X...>
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return Bitset::ForComponent<A>::bitset | Scalar<X...>::MakeBitset();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return std::is_same<TComponent, A>::value || Scalar<X...>::template contains<TComponent>();
                }
            };

            template <class...TComponents>
            struct Rgb
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return std::bitset<8>();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return false;
                }
            };

            template <class A, class...X>
            struct Rgb<A,X...>
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return Bitset::ForComponent<A>::bitset | Rgb<X...>::MakeBitset();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return std::is_same<TComponent, A>::value || Rgb<X...>::template contains<TComponent>();
                }
            };

            template <class...TComponents>
            struct Rgba
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return std::bitset<8>();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return false;
                }
            };

            template <class A, class...X>
            struct Rgba<A,X...>
            {
                static constexpr auto MakeBitset() -> std::bitset<8>
                {
                    return Bitset::ForComponent<A>::bitset | Rgba<X...>::MakeBitset();
                }

                template <class TComponent>
                static constexpr auto contains() -> bool
                {
                    return std::is_same<TComponent, A>::value || Rgba<X...>::template contains<TComponent>();
                }
            };

            template <class TDimensions, class TScalar, class TRgb = Rgb<>, class TRgba = Rgba<>>
            class ImageTypes
            {
            public:
                template <class TImage>
                static constexpr auto accepts() -> bool
                {
                    return TDimensions::contains(TImage::dimension) &&
                    (
                     (TImage::pixel::id == Image::Pixel::ID::Scalar && TScalar::template contains<typename TImage::pixel::component_t>()) ||
                     (TImage::pixel::id == Image::Pixel::ID::Rgb && TRgb::template contains<typename TImage::pixel::component_t>()) ||
                     (TImage::pixel::id == Image::Pixel::ID::Rgba && TRgba::template contains<typename TImage::pixel::component_t>())
                     );
                }

                static constexpr auto MakeConstraints() -> Slot::Constraints*
                {
                    return new Slot::Constraints(TDimensions::MakeBitset(),
                                                  TScalar::MakeBitset(),
                                                  TRgb::MakeBitset(),
                                                  TRgba::MakeBitset());
                }
            };
        }
    }
}