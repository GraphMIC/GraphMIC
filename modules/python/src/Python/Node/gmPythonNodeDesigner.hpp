#pragma once

#include <QObject>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Object;

            class Designer : public QObject
            {
                Q_OBJECT
                Q_PROPERTY(gm::Python::Node::Object* node READ getNode NOTIFY nodeChanged);
            private:
                Object* m_node;
                Designer();
            public:
                static Designer* instance;
                static auto Create() -> Designer*;
                auto setNode(Object*) -> void;
                auto getNode() -> Object*;
            signals:
                void nodeChanged();
            };
        }
    }
}