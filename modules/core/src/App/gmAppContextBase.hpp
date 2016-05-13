#pragma once

#include <QObject>

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class Base : public QObject
            {
                Q_OBJECT
                Q_PROPERTY(bool visible READ getVisible NOTIFY visibleChanged);
                Q_PROPERTY(QString name READ getName CONSTANT);
            private:
                bool m_visible;
                QString m_name;
                Base() = delete;
            public:
                Base(const QString&);
                auto getName() -> QString;
                auto setVisible(bool) -> void;
                auto getVisible() -> bool;
                ~Base();
            signals:
                void visibleChanged();
            };
        }
    }
}