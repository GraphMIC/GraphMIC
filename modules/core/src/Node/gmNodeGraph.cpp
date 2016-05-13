#include "gmLog.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeObject.hpp"
#include "gmNodeList.hpp"
#include "gmConnectionList.hpp"
#include "gmConnectionObject.hpp"
#include "gmNotificationController.hpp"

namespace gm
{
    namespace Node
    {
        const int Graph::MaxNodeCount = 256;
        
        Graph::Graph() : m_position({-1,-1}), m_active(false), m_maxLayer(0)
        {
            log_trace(Log::New, this);
            
            this->m_nodeList        = new Node::List(this);
            this->m_connectionList  = new Connection::List();
            this->m_selectionCount  = 0;
            this->m_name            = "New Graph";
            this->m_modified        = true;
        }
        
        auto Graph::setPath(const QString& path) -> void
        {
            log_trace(Log::Set);
            
            this->m_path = path;
            emit this->pathChanged();
        }
        
        auto Graph::getPath() -> QString
        {
            return this->m_path;
        }
        
        auto Graph::getNodes() -> QList<Node::Object*>
        {
            return this->m_nodeList->getNodes();
        }
        
        auto Graph::getConnections() -> QList<Connection::Object*>
        {
            return this->m_connectionList->getConnections();
        }
        
        auto Graph::setModified(bool modified) -> void
        {
            log_trace(Log::Set);
            
            if (this->m_modified != modified)
            {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }
        
        auto Graph::isModified() -> bool
        {
            return this->m_modified;
        }
        
        auto Graph::setName(const QString& name) -> void
        {
            log_trace(Log::Set, name.toStdString());
            
            this->m_name = name;
            emit this->nameChanged();
        }
        
        auto Graph::getName() -> QString
        {
            return this->m_name;
        }
        
        auto Graph::setActive(bool active) -> void
        {
            log_trace(Log::Set, active);
            
            if (this->m_active != active)
            {
                this->m_active = active;
                emit this->activeChanged();
            }
        }
        
        auto Graph::getActive() -> bool
        {
            return this->m_active;
        }
        
        auto Graph::getNodeList() -> Node::List*
        {
            log_trace(Log::Get);
            
            return this->m_nodeList;
        }
        
        auto Graph::getConnectionList() -> Connection::List*
        {
            log_trace(Log::Get);
            
            return this->m_connectionList;
        }
        
        auto Graph::deleteSelection() -> void
        {
            log_trace(Log::Func);
            
            for (auto sel : this->m_selection)
            {
                sel->deleteObject();
            }
        }
        
        auto Graph::setSelection(Selectable* selectable) -> void
        {
            log_trace(Log::Set, selectable);
            
            this->clearSelection();
            
            this->m_selection.clear();
            this->m_selection.append(selectable);
            selectable->setSelected(true);
            setSelectionCount(1);
        }
        
        auto Graph::addSelection(Selectable* selectable) -> void
        {
            log_trace(Log::Func);
            
            this->m_selection.append(selectable);
            selectable->setSelected(true);
            setSelectionCount(this->m_selectionCount + 1);
        }
        
        auto Graph::removeSelection(Selectable* selectable) -> void
        {
            log_trace(Log::Func);

            this->m_selection.removeOne(selectable);
            selectable->setSelected(false);
            setSelectionCount(this->m_selectionCount - 1);
        }
        
        auto Graph::clearSelection() -> void
        {
            log_trace(Log::Func);
            
            for (auto sel : this->m_selection)
            {
                sel->setSelected(false);
            }
            
            this->m_selection.clear();
            this->setSelectionCount(0);
        }
        
        auto Graph::setSelectionCount(int count) -> void
        {
            log_trace(Log::Set, count);
            
            if (this->m_selectionCount != count)
            {
                this->m_selectionCount = count;
                emit this->selectionCountChanged();
            }
        }
        
        auto Graph::getSelectionCount() -> int
        {
            log_trace(Log::Get);
            
            return this->m_selectionCount;
        }
    
        auto Graph::setPosition(int x, int y) -> void
        {
            log_trace(Log::Set, "x: " << x << ", y: " << y);
            
            this->m_position.setX(x);
            this->m_position.setY(y);
        }
        
        auto Graph::getPosition() -> QPoint
        {
            log_trace(Log::Get);
            
            return this->m_position;
        }
        
        auto Graph::addConnection(Connection::Object* connection) -> void
        {
            log_trace(Log::Func);
            
            this->m_connectionList->addConnection(connection);

            this->setModified(true);
        }
        
        auto Graph::deleteConnection(Connection::Object* connection) -> void
        {
            log_trace(Log::Func);
            
            if (connection->getSelected())
            {
                removeSelection(connection);
            }
            
            this->m_connectionList->removeConnection(connection);
            delete connection;

            this->setModified(true);
        }
        
        auto Graph::getNodeCount() -> int
        {
            return this->m_nodeList->rowCount();
        }
        
        auto Graph::addNode(Object* node) -> void
        {
            log_trace(Log::Func, node);
            
            this->m_nodeList->addNode(node);
            node->setLayer(++m_maxLayer);

            this->setModified(true);
        }
        
        auto Graph::sortNodeLayers() -> void
        {
            log_trace(Log::Func);
            
            QList<Object*> nodes = this->m_nodeList->getNodes();
            
            QMap<int, Object*> map;
            
            for (auto node : nodes)
            {
                map[node->getLayer()] = node;
            }

            auto layer  = 0;
            nodes       = map.values();
            
            for (auto node : nodes)
            {
                node->setLayer(++layer);
            }
            
            this->m_maxLayer = layer;
        }
        
        auto Graph::raiseNode(Object* node) -> void
        {
            log_trace(Log::Func);
            
            if (node->getLayer() < this->m_maxLayer)
            {
                node->setLayer(++m_maxLayer);
            }
            
            if (m_maxLayer > MaxNodeCount)
            {
                sortNodeLayers();
            }
        }
        
        auto Graph::execute() -> void
        {
            log_trace(Log::Func);
        }
        
        auto Graph::remove() -> void
        {
            log_trace(Log::Func, this);
            
            Editor::instance->deleteGraph(this);
        }
        
        auto Graph::activate() -> void
        {
            log_trace(Log::Func, this);
            
            Editor::instance->setGraph(this);
        }

        auto Graph::removeNode(Object* node) -> void
        {
            log_trace(Log::Func, node);

            if (!node)
            {
                return;
            }
            
            if (node->getSelected())
            {
                removeSelection(node);
            }

            this->m_nodeList->removeNode(node);
        }

        auto Graph::deleteNode(Object* node) -> void
        {
            log_trace(Log::Func, node);

            this->removeNode(node);
            delete node;

            this->setModified(true);
        }
        
        Graph::~Graph()
        {
            log_trace(Log::Del, this);
        
            delete this->m_connectionList;
            delete this->m_nodeList;
        }
    }
}