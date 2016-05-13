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
        namespace Preview
        {
            class GM_CORE_EXPORT Controller : public QObject
            {
                Q_OBJECT
            public:
                static Controller* instance;
            public:
                Controller();
                virtual auto setNode(Node::Object*) -> void = 0;
                virtual auto getNode() -> Node::Object* = 0;
                virtual auto onNodeDataChanged() -> void = 0;
                virtual auto reset() -> void = 0;
                virtual ~Controller();
            };
        }
    }
}