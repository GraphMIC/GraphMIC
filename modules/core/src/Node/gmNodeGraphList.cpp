#include "gmLog.hpp"

#include "gmNodeGraphList.hpp"
#include "gmNodeGraph.hpp"

#include <iostream>

namespace gm
{
    namespace Node
    {
        GraphList::GraphList() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto GraphList::getGraphs() -> QList<Graph*>
        {
            log_trace(Log::Get);
            
            return this->m_graphs;
        }
        
        auto GraphList::addGraph(Graph* graph) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_graphs.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_graphs.append(graph);
            endInsertRows();
        }
        
        auto GraphList::removeGraph(Graph* graph) -> void
        {
            if (!graph)
            {
                return;
            }
            
            int index = this->m_graphs.indexOf(graph);
            
            log_trace(Log::Func, graph << " at index " << index);
            
            beginRemoveRows(QModelIndex(), index, index);
            std::cout << "removed: " << this->m_graphs.removeOne(graph) << std::endl;
            endRemoveRows();
        }
        
        auto GraphList::clear() -> void
        {
            log_trace(Log::Func);
            
            auto instances = this->m_graphs;
            
            beginResetModel();
            this->m_graphs.clear();
            endResetModel();
            
            for (auto graph : instances)
            {
                delete graph;
            }
        }
        
        auto GraphList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == GraphRole && index.isValid())
            {
                v.setValue(this->m_graphs.at(index.row()));
            }
            
            return v;
        }
        
        auto GraphList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[GraphRole] = "graph";
            return roles;
        }
        
        auto GraphList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_graphs.size();
        }
        
        GraphList::~GraphList()
        {
            log_trace(Log::Del, this);
            
            this->clear();
        }
    }
}