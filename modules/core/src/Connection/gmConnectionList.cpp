#include "gmLog.hpp"
#include "gmConnectionObject.hpp"
#include "gmConnectionList.hpp"

namespace gm
{
    namespace Connection
    {
        List::List() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto List::getConnections() -> QList<Object*>
        {            
            return this->m_connections;
        }
        
        auto List::addConnection(Object* connection) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_connections.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_connections.append(connection);
            endInsertRows();
        }
        
        auto List::removeConnection(Object* connection) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_connections.indexOf(connection);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_connections.removeOne(connection);
            endRemoveRows();
        }
        
        auto List::clear() -> void
        {
            log_trace(Log::Func);
         
            QList<Object*> instances = this->m_connections;
            
            beginResetModel();
            this->m_connections.clear();
            endResetModel();
            
            for (auto connection : instances)
            {
                delete connection;
            }
        }
        
        auto List::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == ConnectionRole && index.isValid())
            {
                v.setValue(this->m_connections.at(index.row()));
            }
            
            return v;
        }
        
        auto List::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[ConnectionRole] = "connection";
            return roles;
        }
        
        auto List::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_connections.size();
        }
        
        List::~List()
        {
            log_trace(Log::Del, this);
            
            this->clear();
        }
    }
}
