#include "gmImageAttributes.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Image
    {

        Attributes::Attributes(mitk::Image::Pointer mitkImage)
        {
            log_trace(Log::New, this);

            Pixel::ID pixelID;
            Component::ID componentID;
            unsigned int dimension;

            log_info("pixelType: " << mitkImage->GetPixelType().GetPixelTypeAsString());
            log_info("channels : " << mitkImage->GetPixelType().GetNumberOfComponents());
            log_info("component: " << mitkImage->GetPixelType().GetComponentTypeAsString());
            log_info("dimension: " << mitkImage->GetDimension());

            switch (mitkImage->GetPixelType().GetPixelType())
            {
                case itk::ImageIOBase::SCALAR:  pixelID = Pixel::ID::Scalar; break;
                case itk::ImageIOBase::RGB:     pixelID = Pixel::ID::Rgb; break;
                case itk::ImageIOBase::RGBA:    pixelID = Pixel::ID::Rgba; break;

                default: pixelID = Pixel::ID::Scalar; break;
            }

            switch ((itk::ImageIOBase::IOComponentType) mitkImage->GetPixelType().GetComponentType())
            {
                case itk::ImageIOBase::UCHAR:   componentID = Component::ID::UChar; break;
                case itk::ImageIOBase::USHORT:  componentID = Component::ID::UShort; break;
                case itk::ImageIOBase::UINT:    componentID = Component::ID::UInt; break;
                case itk::ImageIOBase::CHAR:    componentID = Component::ID::Char; break;
                case itk::ImageIOBase::SHORT:   componentID = Component::ID::Short; break;
                case itk::ImageIOBase::INT: 	componentID = Component::ID::Int; break;
                case itk::ImageIOBase::FLOAT:   componentID = Component::ID::Float; break;
                case itk::ImageIOBase::DOUBLE: 	componentID = Component::ID::Double; break;

                default: componentID = Component::ID::Double; break;
            }

            if (mitkImage->GetPixelType().GetNumberOfComponents() == 1)
            {
                pixelID = Pixel::ID::Scalar;
            }

            if (mitkImage->GetPixelType().GetNumberOfComponents() == 3)
            {
                pixelID = Pixel::ID::Rgb;
            }

            if (mitkImage->GetPixelType().GetNumberOfComponents() == 4)
            {
                pixelID = Pixel::ID::Rgba;
            }

            dimension = mitkImage->GetDimension();

            this->m_dimension = dimension;
            this->m_pixelID = pixelID;
            this->m_componentID = componentID;
        }

        Attributes::Attributes(const unsigned int dimension, Pixel::ID pixelID, Component::ID componentID)
        {
            this->m_dimension = dimension;
            this->m_pixelID = pixelID;
            this->m_componentID = componentID;
        }

        auto Attributes::getDimension() -> const unsigned int
        {
            return this->m_dimension;
        }

        auto Attributes::getPixelID() -> const Pixel::ID
        {
            return this->m_pixelID;
        }

        auto Attributes::getComponentID() -> const Component::ID
        {
            return this->m_componentID;
        }
    }
}
