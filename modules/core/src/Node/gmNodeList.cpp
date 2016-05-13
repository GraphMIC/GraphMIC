#include "gmLog.hpp"
#include "gmNodeList.hpp"
#include "gmNodeObject.hpp"

namespace gm
{
    namespace Node
    {
        List::List() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        List::List(Graph* graph) : List()
        {
            this->m_graph = graph;
        }
        
        auto List::getNodes() -> QList<Object*>
        {
            log_trace(Log::Get);
            
            return this->m_nodes;
        }
        
        auto List::addNode(Object* node) -> void
        {
            log_trace(Log::Func);
            
            node->setGraph(this->m_graph);
            
            int index = this->m_nodes.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_nodes.append(node);
            endInsertRows();
        }
        
        auto List::removeNode(Object* node) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_nodes.indexOf(node);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_nodes.removeOne(node);
            endRemoveRows();
        }
        
        auto List::clear() -> void
        {
            log_trace(Log::Func, this);
            
            auto instances = this->m_nodes;
            
            beginResetModel();
            this->m_nodes.clear();
            endResetModel();

            for (auto node : instances)
            {
                delete node;
            }
        }
        
        auto List::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == NodeRole && index.isValid())
            {
                v.setValue(this->m_nodes.at(index.row()));
            }
            
            return v;
        }
        
        auto List::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[NodeRole] = "node";
            return roles;
        }
        
        auto List::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_nodes.size();
        }
        
        List::~List()
        {
            log_trace(Log::Del, this);
            
            this->clear();
        }
    }
}