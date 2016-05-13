#include "gmSlotConstraints.hpp"
#include "gmDataImage.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Slot
    {
        Constraints::Constraints(std::bitset<4> dimensionBits, std::bitset<8> scalarBits, std::bitset<8> rgbBits, std::bitset<8> rgbaBits) :
        m_dimensionBits(dimensionBits),
        m_scalarBits(scalarBits),
        m_rgbBits(rgbBits),
        m_rgbaBits(rgbaBits)
        {
            this->debugPrint();
            this->updateBits();
        }

        auto Constraints::updateBits() -> void
        {
            this->m_scalars.clear();

            for (auto i = 0; i < this->m_scalarBits.size(); ++i)
            {
                int val = this->m_scalarBits[i];
                std::cout << "val: " << val << "\n";

                this->m_scalars.append(val);

            }

            std::cout << "############\n";
            std::cout << "bits: " << this->m_scalarBits.to_string();

            emit this->scalarsChanged();
        }

        auto Constraints::getScalars() -> QList<int>
        {
            return this->m_scalars;
        }

        auto Constraints::accept(Data::Base* data) -> bool
        {
            if (data)
            {
                if (data->getDataType() == Data::Type::Image)
                {
                    auto image = data->as<Data::Image>();

                    auto attributes         = image->getAttributes();
                    auto imageDimension     = attributes->getDimension();
                    auto imagePixelID       = attributes->getPixelID();
                    auto imageComponentID   = attributes->getComponentID();

                    if (!this->dimension(imageDimension))
                    {
                        return false;
                    }

                    switch (imagePixelID)
                    {
                        case Image::Pixel::ID::Scalar:  return this->scalarPixel(imageComponentID);
                        case Image::Pixel::ID::Rgb:     return this->rgbPixel(imageComponentID);
                        case Image::Pixel::ID::Rgba:    return this->rgbaPixel(imageComponentID);
                    }
                }
            }
            return true;
        }

        auto Constraints::debugPrint() -> void
        {
            std::cout << " dim bits    : " << this->m_dimensionBits.to_string() << "\n";
            std::cout << " scalar bits : " << this->m_scalarBits.to_string() << "\n";
            std::cout << " rgb bits    : " << this->m_rgbBits.to_string() << "\n";
            std::cout << " rgba bits   : " << this->m_rgbaBits.to_string() << "\n";
        }

        auto Constraints::dimension(unsigned int dimension) -> bool
        {
            switch (dimension)
            {
                case 1: return m_dimensionBits[0];
                case 2: return m_dimensionBits[1];
                case 3: return m_dimensionBits[2];
                case 4: return m_dimensionBits[3];

                default: return false;
            }
        }

        auto Constraints::scalarPixel(Image::Component::ID scalarComponent) -> bool
        {
            switch (scalarComponent)
            {
                case Image::Component::ID::UChar:  return this->m_scalarBits[0];
                case Image::Component::ID::UShort: return this->m_scalarBits[1];
                case Image::Component::ID::UInt:   return this->m_scalarBits[2];
                case Image::Component::ID::Char:   return this->m_scalarBits[3];
                case Image::Component::ID::Short:  return this->m_scalarBits[4];
                case Image::Component::ID::Int:    return this->m_scalarBits[5];
                case Image::Component::ID::Float:  return this->m_scalarBits[6];
                case Image::Component::ID::Double: return this->m_scalarBits[7];
            }
        }

        auto Constraints::rgbPixel(Image::Component::ID scalarComponent) -> bool
        {
            switch (scalarComponent)
            {
                case Image::Component::ID::UChar:  return this->m_rgbBits[0];
                case Image::Component::ID::UShort: return this->m_rgbBits[1];
                case Image::Component::ID::UInt:   return this->m_rgbBits[2];
                case Image::Component::ID::Char:   return this->m_rgbBits[3];
                case Image::Component::ID::Short:  return this->m_rgbBits[4];
                case Image::Component::ID::Int:    return this->m_rgbBits[5];
                case Image::Component::ID::Float:  return this->m_rgbBits[6];
                case Image::Component::ID::Double: return this->m_rgbBits[7];
            }
        }

        auto Constraints::rgbaPixel(Image::Component::ID scalarComponent) -> bool
        {
            switch (scalarComponent)
            {
                case Image::Component::ID::UChar:  return this->m_rgbaBits[0];
                case Image::Component::ID::UShort: return this->m_rgbaBits[1];
                case Image::Component::ID::UInt:   return this->m_rgbaBits[2];
                case Image::Component::ID::Char:   return this->m_rgbaBits[3];
                case Image::Component::ID::Short:  return this->m_rgbaBits[4];
                case Image::Component::ID::Int:    return this->m_rgbaBits[5];
                case Image::Component::ID::Float:  return this->m_rgbaBits[6];
                case Image::Component::ID::Double: return this->m_rgbaBits[7];
            }
        }
    }
}