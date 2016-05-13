#pragma once

#include "gmNotificationType.hpp"

#include <QObject>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Notification
    {
        class Entry : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Notification::Type type READ getType CONSTANT);
            Q_PROPERTY(gm::Node::Object* node READ getNode CONSTANT);
            Q_PROPERTY(QString title READ getTitle CONSTANT);
            Q_PROPERTY(QString info READ getInfo CONSTANT);
        private:
            friend class Controller;
            static int instanceCount;
            Node::Object* m_node;
            QString m_title;
            QString m_info;
            Type m_type;
        private:
            Entry();
            Entry(const Entry& other);
        public:
            auto getTitle() -> QString;
            auto getInfo() -> QString;
            auto getType() -> Type;
            auto getNode() -> Node::Object*;
            ~Entry();
        public slots:
            void destroy();
        };
    }
}

Q_DECLARE_METATYPE(gm::Notification::Type);