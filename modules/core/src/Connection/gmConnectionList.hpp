#pragma once

#include <QPoint>
#include <QAbstractListModel>

namespace gm
{
    namespace Connection
    {
        class Object;
        
        class List : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                ConnectionRole = Qt::UserRole + 1,
            };
        private:
            QList<Object*> m_connections;
        public:
            List();
            auto getConnections() -> QList<Object*>;
            auto addConnection(Object*) -> void;
            auto removeConnection(Object*) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~List();
        };
    }
}
