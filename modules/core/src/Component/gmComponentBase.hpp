#pragma once

#include "gmLog.hpp"
#include "gmCoreExport.hpp"
#include "gmComponentType.hpp"

#include <QObject>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Component
    {
        class GM_CORE_EXPORT Base : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Node::Object* node READ getNode CONSTANT);
            Q_PROPERTY(gm::Component::Type componentType READ getComponentType CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
            Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
        private:
            bool m_modified;
            QString m_name;
            Node::Object* m_node;
            Type m_componentType;
        public:
            Base() = delete;
            Base(Type, const QString&);
            auto getName() -> QString;
            auto setNode(Node::Object*) -> void;
            auto getNode() -> Node::Object*;
            auto getComponentType() -> Type;
            auto setModified(bool) -> void;
            auto isModified() -> bool;
            template <class R> auto as() -> R*;
            virtual auto moveToMain() -> void;
            virtual ~Base();
        signals:
            void modifiedChanged();
        };
    }
}
