#pragma once

#include "gmCoreExport.hpp"

#include <QObject>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Interface
    {
        namespace Python
        {
            class GM_CORE_EXPORT Controller : public QObject
            {
                Q_OBJECT
            public:
                static Controller* instance;
            public:
                Controller();
                virtual ~Controller();
            };
        }
    }
}