#pragma once

#include "gmCoreExport.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class Image;
    }
    
    namespace Interface
    {
        namespace Viewer
        {
            class GM_CORE_EXPORT Controller : public QObject
            {
                Q_OBJECT
            public:
                static Controller* instance;
            public:
                Controller();
                virtual auto addImage(Data::Image*) -> void = 0;
                virtual ~Controller();
            };
        }
    }
}