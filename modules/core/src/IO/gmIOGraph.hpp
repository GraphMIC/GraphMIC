#pragma once

#include "gmCoreExport.hpp"

#include <QString>

namespace gm
{
    namespace Node
    {
        class Graph;
    }
    
    namespace IO
    {
        namespace Graph
        {
            GM_CORE_EXPORT auto ToJsonFile(const QString& path, gm::Node::Graph* graph) -> void;
            GM_CORE_EXPORT auto FromJsonFile(const QString& path) -> gm::Node::Graph*;
        };
    }
}