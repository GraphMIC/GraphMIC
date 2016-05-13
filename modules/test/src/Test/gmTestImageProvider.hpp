#pragma once

#include <QHash>

namespace gm
{
    namespace Data
    {
        class Image;
    }
    
    namespace Test
    {
        class ImageProvider
        {
        private:
            QHash<QString, Data::Image*> m_imageMap;
        private:
            ImageProvider();
            auto init() -> void;
        public:
            static ImageProvider* instance;
            static auto Create() -> void;
            auto getImage(const QString&) -> Data::Image*;
            ~ImageProvider();
        };
    }
}