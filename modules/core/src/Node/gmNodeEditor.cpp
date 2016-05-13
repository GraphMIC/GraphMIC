#include "gmNodeEditor.hpp"
#include "gmNodeObject.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeList.hpp"
#include "gmNodeFactory.hpp"
#include "gmNodeConnector.hpp"
#include "gmConnectionView.hpp"
#include "gmConnectionList.hpp"
#include "gmNodeGraphList.hpp"

#include "gmLog.hpp"
#include "gmIOFile.hpp"
#include "gmIOGraph.hpp"

#include <QGuiApplication>

namespace gm
{
    namespace Node
    {
        Editor* Editor::instance = nullptr;

        Editor::Editor() : m_graphList(new GraphList{}), m_connector(new Connector()), m_graph(nullptr)
        {
            log_trace(Log::Func);
            
            if (instance)
            {
                throw "instance already existing";
            }

            this->m_gridSize = 25;
            this->m_snap = false;
            this->m_shortcutsEnabled = true;
            instance = this;
        }
        
        auto Editor::init() -> void
        {
            auto graph = new Graph();
            graph->setName("New Graph");
            
            this->addGraph(graph);
        }

        auto Editor::setGridSize(int gridSize) -> void
        {
            log_trace(Log::Set, gridSize);

            if (this->m_gridSize != gridSize)
            {
                this->m_gridSize = gridSize;
                emit this->gridSizeChanged();
            }
        }

        auto Editor::getGridSize() -> int
        {
            return this->m_gridSize;
        }

        auto Editor::setSnap(bool snap) -> void
        {
            log_trace(Log::Set, snap);

            if (this->m_snap != snap)
            {
                this->m_snap = snap;
                emit this->snapChanged();
            }
        }

        auto Editor::getSnap() -> bool
        {
            return this->m_snap;
        }
        
        auto Editor::saveGraph() -> void
        {
            log_trace(Log::Func);
            
            if (!this->m_graph)
            {
                return;
            }
            
            auto path = this->m_graph->getPath();
            
            if (!path.isEmpty())
            {
                emit this->saveGraphState();
                IO::Graph::ToJsonFile(path, this->m_graph);
            }
            else
            {
                this->saveGraphAs();
            }
        }
        
        auto Editor::saveGraphAs() -> void
        {
            log_trace(Log::Func);
            
            if (!this->m_graph)
            {
                return;
            }
            
            auto path = IO::File::SelectNewFile("Save File", "*.graph");
            
            if (!path.isEmpty())
            {
                emit this->saveGraphState();
                IO::Graph::ToJsonFile(path, this->m_graph);
            }
        }
        
        auto Editor::loadGraph() -> void
        {
            log_trace(Log::Func);
            
            auto path = IO::File::SelectExistingFile("Load graph", "*.graph");
            
            if (!path.isEmpty())
            {
                this->addGraph(IO::Graph::FromJsonFile(path));
            }
        }

        auto Editor::setShortcutsEnabled(bool shortcutsEnabled) -> void
        {
            this->m_shortcutsEnabled = shortcutsEnabled;
        }

        auto Editor::onKeyPressed(int key, int modifiers, QString string) -> bool
        {
            if (!this->m_shortcutsEnabled)
            {
                return false;
            }

            if (!this->m_graph)
            {
                if (modifiers == Qt::ControlModifier)
                {
                    if (key == Qt::Key_O)
                    {
                        this->loadGraph();
                    }
                    else if (key == Qt::Key_N || key == Qt::Key_T)
                    {
                        this->createGraph();
                    }
                    else if (key == Qt::Key_W)
                    {
                        this->deleteGraph(this->m_graph);
                    }
                }
                
                return true;
            }
            
            if (modifiers == Qt::ControlModifier)
            {
                if (key == Qt::Key_S)
                {
                    this->saveGraph();
                    return true;
                }
                if (key == Qt::Key_O)
                {
                    this->loadGraph();
                    return true;
                }
                if (key == Qt::Key_N)
                {
                    this->createGraph();
                    return true;
                }
                if (key == Qt::Key_W)
                {
                    this->deleteGraph(this->m_graph);
                    return true;
                }
            }
            
            return false;
        }
        
        auto Editor::getGraphList() -> GraphList*
        {
            return this->m_graphList;
        }
                
        auto Editor::Create() -> Editor*
        {
            log_trace(Log::Func);
            
            return new Editor();
        }
        
        auto Editor::createGraph() -> void
        {
            log_trace(Log::Func);
            
            auto graph = new Graph();
            graph->setName("New Graph");
            this->addGraph(graph);
        }
        
        auto Editor::getConnector() -> Connector*
        {
            return this->m_connector;
        }
        
        auto Editor::setSpawn(int x, int y) -> void
        {
            log_trace(Log::Set, "x: " << x << ", y: " << y);
            
            this->m_spawn.setX(x);
            this->m_spawn.setY(y);
        }
        
        auto Editor::addGraph(Graph* graph) -> void
        {
            log_trace(Log::Func, graph);
            
            this->m_graphList->addGraph(graph);
            this->setGraph(graph);
        }
        
        auto Editor::deleteGraph(Graph* graph) -> void
        {
            log_trace(Log::Func, graph);
            
            if (this->m_graph == graph)
            {
                Graph* newGraph = nullptr;
                auto graphs     = this->m_graphList->getGraphs();
                auto index      = graphs.indexOf(graph);
                auto maxIndex   = graphs.count() - 1;
                auto newIndex   = std::min(index + 1, maxIndex);
                
                if (newIndex == index)
                {
                    if (newIndex < maxIndex)
                    {
                        ++newIndex;
                    }
                    else
                    {
                        --newIndex;
                    }
                }
                
                if (newIndex > -1)
                {
                    newGraph = graphs.at(newIndex);
                }
                
                this->setGraph(newGraph);
            }
            
            this->m_graphList->removeGraph(graph);
            delete graph;
        }
        
        auto Editor::select(Selectable* selectable) -> void
        {
            log_trace(Log::Func);
            
            if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
            {
                this->m_graph->addSelection(selectable);
            }
            else
            {
                this->m_graph->setSelection(selectable);
            }
        }

        auto Editor::clearSelection() -> void
        {
            log_trace(Log::Func);

            if (this->m_graph)
            {
                this->m_graph->clearSelection();
            }
        }

        auto Editor::unselect(Selectable* selectable) -> void
        {
            log_trace(Log::Func);
            
            this->m_graph->removeSelection(selectable);
        }
        
        auto Editor::deleteSelection() -> void
        {
            log_trace(Log::Func);
            
            this->m_graph->deleteSelection();
        }
        
        auto Editor::getSpawn() -> QPoint
        {
            log_trace(Log::Get);
            
            return this->m_spawn;
        }
        
        auto Editor::setGraph(Graph* graph) -> void
        {
            log_trace(Log::Set, graph);
            
            if (this->m_graph != graph)
            {
                if (this->m_graph)
                {
                    emit this->saveGraphState();
                    this->m_graph->setActive(false);
                }
                
                this->m_graph = graph;
                
                if (this->m_graph)
                {
                    this->m_graph->setActive(true);
                }
                
                emit this->graphChanged();
            }
        }
        
        auto Editor::getGraph() -> Graph*
        {
            log_trace(Log::Get);
            
            return this->m_graph;
        }
                
        Editor::~Editor()
        {
            log_trace(Log::Del, this);
        }
    }
}