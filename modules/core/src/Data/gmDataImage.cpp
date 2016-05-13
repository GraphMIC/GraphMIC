#include "gmDataImage.hpp"

#include "gmImageAttributes.hpp"
#include "gmDebugController.hpp"

#include "gmLog.hpp"

#include <mitkIOUtil.h>

namespace gm
{
    namespace Data
    {
        Type Image::DataType = Type::Image;

        Image::Image(mitk::Image::Pointer mitkImage) : Base(DataType)
        {
            log_trace(Log::New);

            this->m_mitkImage       = mitkImage;
            this->m_mitkDataNode    = mitk::DataNode::New();
            this->m_attributes      = new gm::Image::Attributes(mitkImage);

            this->m_mitkDataNode->SetData(mitkImage);

            Debug::Controller::instance->incImageCount();
        }

        auto Image::FromFile(const QString& filePath) -> Image*
        {
            auto mitkImage = mitk::IOUtil::LoadImage(filePath.toStdString());
            auto image = new Image(mitkImage);

            return image;
        }

        auto Image::saveToDir(const QString& filePath) -> void
        {
            mitk::IOUtil::Save(this->m_mitkImage, filePath.toStdString().c_str());
        }

        auto Image::getMitkImage() -> mitk::Image::Pointer
        {
            return this->m_mitkImage;
        }

        auto Image::getMitkDataNode() -> mitk::DataNode::Pointer
        {
            return this->m_mitkDataNode;
        }

        auto Image::getAttributes() -> gm::Image::Attributes*
        {
            return this->m_attributes;
        }

        auto Image::getIsImage() -> bool
        {
            return true;
        }

        auto Image::printDebugInfo() -> void
        {
            this->m_mitkImage->Print(std::cout);
        }

        auto Image::getDimension() -> unsigned int
        {
            return this->m_attributes->getDimension();
        }

        auto Image::getComponentString() -> QString
        {
            switch (this->m_attributes->getComponentID())
            {
                case gm::Image::Component::ID::UChar: return "UChar";
                case gm::Image::Component::ID::UShort: return "UShort";
                case gm::Image::Component::ID::UInt: return "UInt";
                case gm::Image::Component::ID::Char: return "Char";
                case gm::Image::Component::ID::Short: return "Short";
                case gm::Image::Component::ID::Int: return "Int";
                case gm::Image::Component::ID::Float: return "Float";
                case gm::Image::Component::ID::Double: return "Double";
            }
        }

        auto Image::getPixelString() -> QString
        {
            switch (this->m_attributes->getPixelID())
            {
                case gm::Image::Pixel::ID::Scalar: return "Scalar";
                case gm::Image::Pixel::ID::Rgb: return "Rgb";
                case gm::Image::Pixel::ID::Rgba: return "Rgba";
            }
        }

        Image::~Image()
        {
            Debug::Controller::instance->decImageCount();
            m_mitkDataNode->RemoveAllObservers();
            m_mitkDataNode->ReleaseData();
        }
    }
}