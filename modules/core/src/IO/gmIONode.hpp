#pragma once

#include "gmCoreExport.hpp"

#include <QString>
#include <QJsonObject>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace IO
    {
        namespace Node
        {
            GM_CORE_EXPORT auto ToJsonObject(gm::Node::Object* node) -> QJsonObject;
            GM_CORE_EXPORT auto FromJsonObject(QJsonObject) -> gm::Node::Object*;
        };
    }
}