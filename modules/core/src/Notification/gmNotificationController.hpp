#pragma once

#include "gmNotificationType.hpp"
#include "gmCoreExport.hpp"

#include <QObject>
#include <QQmlListProperty>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Notification
    {
        class List;
        class Entry;
        
        class GM_CORE_EXPORT Controller : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Notification::List* entries READ getEntries CONSTANT);
            Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged);
        private:
            List* m_entries;
            bool m_visible;
            Controller();
        public:
            static Controller* instance;
            auto setVisible(bool) -> void;
            auto isVisible() -> bool;
            auto getEntries() -> List*;
            static auto Post(Type, const QString&, Node::Object* = nullptr) -> void;
            static auto Create() -> Controller*;
            ~Controller();
        private slots:
            void post(const QString&);
        public slots:
            void show();
            void clear();
        signals:
            void visibleChanged();
            void entriesChanged();
        };
    }
}