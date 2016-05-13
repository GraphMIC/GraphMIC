#pragma once

#include <QPoint>
#include <QAbstractListModel>

namespace gm
{
    namespace Node
    {
        class Graph;
        
        class GraphList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                GraphRole = Qt::UserRole + 1,
            };
        private:
            QList<Node::Graph*> m_graphs;
        public:
            GraphList();
            auto getGraphs() -> QList<Graph*>;
            auto addGraph(Graph*) -> void;
            auto removeGraph(Graph*) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~GraphList();
        };
    }
}
