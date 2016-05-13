#pragma once

#include "gmComponentType.hpp"

#include <QObject>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Object;

            class Component : public QObject
            {
                Q_OBJECT
                Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
                Q_PROPERTY(gm::Component::Type componentType READ getComponentType CONSTANT);
                Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged);
            private:
                gm::Component::Type m_componentType;
                QString m_name;
                Object* m_node;
                bool m_selected;
            public:
                Component() = delete;
                Component(gm::Component::Type, Object*);
                auto setSelected(bool) -> void;
                auto isSelected() -> bool;
                auto getComponentType() -> gm::Component::Type;
                auto setName(const QString&) -> void;
                auto getName() -> QString;
            public slots:
                void remove();
                void select();
            signals:
                void selectedChanged();
                void nameChanged();
            };
        }
    }
}
