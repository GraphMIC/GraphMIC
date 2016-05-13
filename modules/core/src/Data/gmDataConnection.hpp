#pragma once

#include <QMetaType>

namespace gm
{
    namespace Data
    {
        enum Connection
        {
            Required,
            Optional
        };
    }
}

Q_DECLARE_METATYPE(gm::Data::Connection);