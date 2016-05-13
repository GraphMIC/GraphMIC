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
        class Graph;
        class Selectable;
        class Connector;
        class GraphList;
        
        class GM_CORE_EXPORT Editor : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Node::GraphList* graphList READ getGraphList CONSTANT);
            Q_PROPERTY(gm::Node::Graph* graph READ getGraph NOTIFY graphChanged);
            Q_PROPERTY(gm::Node::Connector* connector READ getConnector CONSTANT);
            Q_PROPERTY(bool snap READ getSnap WRITE setSnap NOTIFY snapChanged);
            Q_PROPERTY(int gridSize READ getGridSize WRITE setGridSize NOTIFY gridSizeChanged);
        private:
            GraphList* m_graphList;
            Connector* m_connector;
            QPoint m_spawn;
            Graph* m_graph;
            bool m_snap;
            bool m_shortcutsEnabled;
            int m_gridSize;
            Editor();
        public:
            static Editor* instance;
            auto init() -> void;
            auto getGraphList() -> GraphList*;
            auto getConnector() -> Connector*;
            auto setShortcutsEnabled(bool) -> void;
            auto setSnap(bool) -> void;
            auto getSnap() -> bool;
            auto setGraph(Graph*) -> void;
            auto getGraph() -> Graph*;
            auto getSpawn() -> QPoint;
            auto setGridSize(int) -> void;
            auto getGridSize() -> int;
            auto addGraph(Graph*) -> void;
            auto deleteGraph(Graph*) -> void;
            auto centerOn(QPoint) -> void;
            auto select(Selectable*) -> void;
            auto unselect(Selectable*) -> void;
            static auto Create() -> Editor*;
            ~Editor();
        public slots:
            void setSpawn(int, int);
            void deleteSelection();
            void clearSelection();
            void saveGraph();
            void saveGraphAs();
            void loadGraph();
            void createGraph();
            bool onKeyPressed(int, int, QString);
        signals:
            void snapChanged();
            void gridSizeChanged();
            void moveToNode(gm::Node::Object* node);
            void graphChanged();
            void saveGraphState();
        };
    }
}
