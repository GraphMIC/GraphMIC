#pragma once

#include "gmCoreExport.hpp"
#include "gmAppMenu.hpp"

#include <QPoint>
#include <QObject>

namespace gm
{
    namespace Connection
    {
        class Object;
    }
    
    namespace Node
    {
        class Object;
        
        class GM_CORE_EXPORT PropertyController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Node::Object* node READ getNode NOTIFY nodeChanged);
            Q_PROPERTY(bool expanded READ getExpanded WRITE setExpanded NOTIFY expandedChanged);
        private:
            Object* m_node;
            bool m_expanded;
        private:
            PropertyController();
        public:
            static PropertyController* instance;
            auto setExpanded(bool) -> void;
            auto getExpanded() -> bool;
            auto setNode(Object*) -> void;
            auto getNode() -> Object*;
            auto reset() -> void;
            static auto Create() -> PropertyController*;
            ~PropertyController();
        signals:
            void nodeChanged();
            void expandedChanged();
        };
    }
}
