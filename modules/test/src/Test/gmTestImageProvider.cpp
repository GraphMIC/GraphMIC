#include "gmTestImageProvider.hpp"

#include "gmApp.hpp"
#include "gmIOFile.hpp"
#include "gmIOPath.hpp"
#include "gmDataImage.hpp"
#include "gmImageAttributes.hpp"
#include "gmSlotConstraints.hpp"
#include "gmSlotOutput.hpp"

#include "gmAsync.hpp"

#include <iostream>

namespace gm
{
    namespace Test
    {
        ImageProvider* ImageProvider::instance = nullptr;
        
        ImageProvider::ImageProvider()
        {
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }
        
        auto ImageProvider::Create() -> void
        {
            auto provider = new ImageProvider();
            provider->init();
        }
        
        auto ImageProvider::init() -> void
        {
            const auto suffix = QString(".nrrd");

            QStringList imageFiles = IO::File::GetFilesFromDirectory(Application::instance->getResourceDir() + "/tests/data", suffix);

            for (auto imageFile : imageFiles)
            {
                auto image = Data::Image::FromFile(imageFile);

                Async::MoveToMain(image);

                auto name = IO::Path::ExtractFileName(imageFile);
                name.chop(suffix.length());

                this->m_imageMap[name] = image;
            }
        }

        auto ImageProvider::getImage(const QString& name) -> Data::Image*
        {
            if (this->m_imageMap.contains(name))
            {
                return this->m_imageMap[name];
            }
            
            return nullptr;
        }

        ImageProvider::~ImageProvider()
        {
            for (auto image : this->m_imageMap)
            {
                delete image;
            }
            
            this->m_imageMap.clear();
            
            instance = nullptr;
        }
    }
}