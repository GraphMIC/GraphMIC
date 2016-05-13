#pragma once

#include <QPoint>
#include <QAbstractListModel>

namespace gm
{
    namespace Node
    {
        class Object;
        class Graph;
        
        class List : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                NodeRole = Qt::UserRole + 1,
            };
        private:
            QList<Node::Object*> m_nodes;
            QPoint m_position;
            Graph* m_graph;
            List();
        public:
            List(Graph*);
            auto getNodes() -> QList<Node::Object*>;
            auto addNode(Object*) -> void;
            auto removeNode(Object*) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~List();
        };
    }
}
